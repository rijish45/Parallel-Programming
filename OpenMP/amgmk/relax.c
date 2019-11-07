/*BHEADER**********************************************************************
 * Copyright (c) 2006   The Regents of the University of California.
 * Produced at the Lawrence Livermore National Laboratory.
 * Written by the HYPRE team. UCRL-CODE-222953.
 * All rights reserved.
 *
 * This file is part of HYPRE (see http://www.llnl.gov/CASC/hypre/).
 * Please see the COPYRIGHT_and_LICENSE file for the copyright notice, 
 * disclaimer, contact information and the GNU Lesser General Public License.
 *
 * HYPRE is free software; you can redistribute it and/or modify it under the 
 * terms of the GNU General Public License (as published by the Free Software
 * Foundation) version 2.1 dated February 1999.
 *
 * HYPRE is distributed in the hope that it will be useful, but WITHOUT ANY 
 * WARRANTY; without even the IMPLIED WARRANTY OF MERCHANTABILITY or FITNESS 
 * FOR A PARTICULAR PURPOSE.  See the terms and conditions of the GNU General
 * Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * $Revision: 2.8 $
 ***********************************************************************EHEADER*/




/******************************************************************************
 *
 * Relaxation scheme
 *
 *****************************************************************************/

#include "headers.h"

/*--------------------------------------------------------------------------
 * hypre_BoomerAMGSeqRelax
 *--------------------------------------------------------------------------*/

int  hypre_BoomerAMGSeqRelax( hypre_CSRMatrix *A,
                        hypre_Vector    *f,
                        hypre_Vector    *u)
{
   double         *A_diag_data  = hypre_CSRMatrixData(A);
   int            *A_diag_i     = hypre_CSRMatrixI(A);
   int            *A_diag_j     = hypre_CSRMatrixJ(A);

   int             n       = hypre_CSRMatrixNumRows(A);
   
   double         *u_data  = hypre_VectorData(u);

   double         *f_data  = hypre_VectorData(f);

   double         *tmp_data;
   
   double          res;

   
   int             i, j;
   int             ii, jj;
   int             ns, ne, size, rest;
   int             relax_error = 0;

   /*-----------------------------------------------------------------------
    * Switch statement to direct control based on relax_type:
    *     relax_type = 3 -> hybrid: SOR-J mix off-processor, SOR on-processor
    *     		    with outer relaxation parameters (forward solve)
    *-----------------------------------------------------------------------*/
   
   /*-----------------------------------------------------------------
    * Relax all points.
    *-----------------------------------------------------------------*/
   
#pragma omp parallel for default(shared) private(i, jj)
   for (i = 0; i < n; i++)	/* interior points first */
   {
     
     /*-----------------------------------------------------------
      * If diagonal is nonzero, relax point i; otherwise, skip it.
      *-----------------------------------------------------------*/ 
     if ( A_diag_data[A_diag_i[i]] != 0.0)
     {
       res = f_data[i];
       for (jj = A_diag_i[i]+1; jj < A_diag_i[i+1]; jj++)
       {
	 ii = A_diag_j[jj];
	 res -= A_diag_data[jj] * u_data[ii];
       }
       u_data[i] = res / A_diag_data[A_diag_i[i]];
     }
   }
   
   return(relax_error); 
}
