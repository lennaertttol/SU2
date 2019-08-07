/*!
 * \file CDiscAdjVariable.hpp
 * \brief Main class for defining the variables of the adjoint solver.
 * \author F. Palacios, T. Economon
 * \version 6.2.0 "Falcon"
 *
 * The current SU2 release has been coordinated by the
 * SU2 International Developers Society <www.su2devsociety.org>
 * with selected contributions from the open-source community.
 *
 * The main research teams contributing to the current release are:
 *  - Prof. Juan J. Alonso's group at Stanford University.
 *  - Prof. Piero Colonna's group at Delft University of Technology.
 *  - Prof. Nicolas R. Gauger's group at Kaiserslautern University of Technology.
 *  - Prof. Alberto Guardone's group at Polytechnic University of Milan.
 *  - Prof. Rafael Palacios' group at Imperial College London.
 *  - Prof. Vincent Terrapon's group at the University of Liege.
 *  - Prof. Edwin van der Weide's group at the University of Twente.
 *  - Lab. of New Concepts in Aeronautics at Tech. Institute of Aeronautics.
 *
 * Copyright 2012-2019, Francisco D. Palacios, Thomas D. Economon,
 *                      Tim Albring, and the SU2 contributors.
 *
 * SU2 is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * SU2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with SU2. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "CVariable.hpp"

/*!
 * \class CDiscAdjVariable
 * \brief Main class for defining the variables of the adjoint solver.
 * \ingroup Discrete_Adjoint
 * \author T. Albring.
 */
class CDiscAdjVariable final : public CVariable {
private:
  Mat_t Sensitivity; /* Vector holding the derivative of target functional with respect to the coordinates at this node*/
  Mat_t Solution_Direct;
  Mat_t DualTime_Derivative;
  Mat_t DualTime_Derivative_n;

  Mat_t Cross_Term_Derivative;
  Mat_t Geometry_CrossTerm_Derivative;
  Mat_t Geometry_CrossTerm_Derivative_Flow;

  Mat_t Solution_Geometry;
  Mat_t Solution_Geometry_Old;
  Mat_t Geometry_Direct;

  Mat_t Solution_BGS;
  Mat_t Solution_BGS_k;
  Mat_t Solution_Geometry_BGS_k;

public:
  /*!
   * \brief Constructor of the class.
   */
  CDiscAdjVariable() = default;

  /*!
   * \brief Destructor of the class.
   */
  ~CDiscAdjVariable() = default;

  /*!
   * \overload
   * \param[in] sol - Pointer to the adjoint value (initialization value).
   * \param[in] npoint - Number of points/nodes/vertices in the domain.
   * \param[in] ndim - Number of dimensions of the problem.
   * \param[in] nvar - Number of variables of the problem.
   * \param[in] config - Definition of the particular problem.
   */
  CDiscAdjVariable(const su2double* sol, Idx_t npoint, Idx_t ndim, Idx_t nvar, CConfig *config);

  /*!
   * \brief Set the sensitivity at the node
   * \param[in] iDim - spacial component
   * \param[in] val - value of the Sensitivity
   */
  inline void SetSensitivity(Idx_t iPoint, Idx_t iDim, su2double val) { Sensitivity(iPoint,iDim) = val;}

  /*!
   * \brief Get the Sensitivity at the node
   * \param[in] iDim - spacial component
   * \return value of the Sensitivity
   */
  inline su2double GetSensitivity(Idx_t iPoint, Idx_t iDim) const { return Sensitivity(iPoint,iDim); }

  inline void SetDual_Time_Derivative(Idx_t iPoint, Idx_t iVar, su2double der) { DualTime_Derivative(iPoint,iVar) = der; }

  inline void SetDual_Time_Derivative_n(Idx_t iPoint, Idx_t iVar, su2double der) { DualTime_Derivative_n(iPoint,iVar) = der; }

  inline su2double GetDual_Time_Derivative(Idx_t iPoint, Idx_t iVar) const { return DualTime_Derivative(iPoint,iVar); }

  inline su2double GetDual_Time_Derivative_n(Idx_t iPoint, Idx_t iVar) const { return DualTime_Derivative_n(iPoint,iVar); }

  inline void SetSolution_Direct(Idx_t iPoint, const su2double *val_solution_direct) {
    for (Idx_t iVar = 0; iVar < nVar; iVar++)
      Solution_Direct(iPoint,iVar) = val_solution_direct[iVar];
  }

  inline su2double* GetSolution_Direct(Idx_t iPoint) { return Solution_Direct[iPoint]; }

  /*!
   * \brief Set the restart geometry (coordinate of the converged solution)
   * \param[in] val_geometry_direct - Value of the restart coordinate.
   */
  inline void SetGeometry_Direct(Idx_t iPoint, const su2double *val_geometry_direct) {
    for (Idx_t iDim = 0; iDim < nDim; iDim++)
      Geometry_Direct(iPoint,iDim) = val_geometry_direct[iDim];
  }

  /*!
   * \brief Get the restart geometry (coordinate of the converged solution).
   * \return Pointer to the restart coordinate vector.
   */
  inline su2double *GetGeometry_Direct(Idx_t iPoint) { return Geometry_Direct[iPoint]; }

  /*!
   * \brief Get the restart geometry (coordinate of the converged solution).
   * \return Coordinate iDim of the geometry_direct vector.
   */
  inline su2double GetGeometry_Direct(Idx_t iPoint, Idx_t iDim) const { return Geometry_Direct(iPoint,iDim); }

  /*!
   * \brief Get the geometry solution.
   * \param[in] iDim - Index of the coordinate.
   * \return Value of the solution for the index <i>iDim</i>.
   */
  inline su2double GetSolution_Geometry(Idx_t iPoint, Idx_t iDim) const { return Solution_Geometry(iPoint,iDim); }

  /*!
   * \brief Set the value of the mesh solution (adjoint).
   * \param[in] val_solution_geometry - Solution of the problem (acceleration).
   */
  inline void SetSolution_Geometry(Idx_t iPoint, const su2double *val_solution_geometry) {
    for (Idx_t iDim = 0; iDim < nDim; iDim++)
      Solution_Geometry(iPoint,iDim) = val_solution_geometry[iDim];
  }

  /*!
   * \brief A virtual member. Set the value of the mesh solution (adjoint).
   * \param[in] val_solution_geometry - Solution of the problem (acceleration).
   */
  inline void SetSolution_Geometry(Idx_t iPoint, Idx_t iVar, su2double val_solution_geometry) {
    Solution_Geometry(iPoint,iVar) = val_solution_geometry;
  }

  /*!
   * \brief A virtual member. Get the geometry solution.
   * \param[in] iVar - Index of the variable.
   * \return Value of the solution for the index <i>iVar</i>.
   */
  inline su2double GetGeometry_CrossTerm_Derivative(Idx_t iPoint, Idx_t iVar) const {
    return Geometry_CrossTerm_Derivative(iPoint,iVar);
  }

  /*!
   * \brief A virtual member. Set the value of the mesh solution (adjoint).
   * \param[in] der - cross term derivative.
   */
  inline void SetGeometry_CrossTerm_Derivative(Idx_t iPoint, Idx_t iDim, su2double der) {
    Geometry_CrossTerm_Derivative(iPoint,iDim) = der;
  }

  /*!
   * \brief Get the mesh cross term derivative from the flow solution.
   * \param[in] iVar - Index of the variable.
   * \return Value of the solution for the index <i>iVar</i>.
   */
  inline su2double GetGeometry_CrossTerm_Derivative_Flow(Idx_t iPoint, Idx_t iVar) const {
    return Geometry_CrossTerm_Derivative_Flow(iPoint,iVar);
  }

  /*!
   * \brief Set the value of the mesh cross term derivative from the flow solution (adjoint).
   * \param[in] der - cross term derivative.
   */
  inline void SetGeometry_CrossTerm_Derivative_Flow(Idx_t iPoint, Idx_t iDim, su2double der) {
    Geometry_CrossTerm_Derivative_Flow(iPoint,iDim) = der;
  }

  /*!
   * \brief Set the value of the mesh solution (adjoint).
   * \param[in] val_solution - Solution of the problem (acceleration).
   */
  inline void Set_OldSolution_Geometry(Idx_t iPoint) {
    for (Idx_t iDim = 0; iDim < nDim; iDim++)
      Solution_Geometry_Old(iPoint,iDim) = Solution_Geometry(iPoint,iDim);
  }

  /*!
   * \brief Get the value of the old geometry solution (adjoint).
   * \param[out] val_solution - old adjoint solution for coordinate iDim
   */
  inline su2double Get_OldSolution_Geometry(Idx_t iPoint, Idx_t iDim) const {
    return Solution_Geometry_Old(iPoint,iDim);
  }

  /*!
   * \brief Set the value of the adjoint solution in the current BGS subiteration.
   */
  inline void Set_BGSSolution(Idx_t iPoint, Idx_t iDim, su2double val_solution) {
    Solution_BGS(iPoint,iDim) = val_solution;
  }

  /*!
   * \brief Set the value of the adjoint solution in the previous BGS subiteration.
   */
  inline void Set_BGSSolution_k(Idx_t iPoint) {
    for (Idx_t iVar = 0; iVar < nVar; iVar++) Solution_BGS_k(iPoint,iVar) = Solution_BGS(iPoint,iVar);
  }

  /*!
   * \brief Get the value of the adjoint solution in the previous BGS subiteration.
   * \param[out] val_solution - adjoint solution in the previous BGS subiteration.
   */
  inline su2double Get_BGSSolution(Idx_t iPoint, Idx_t iDim) const { return Solution_BGS(iPoint,iDim);}

  /*!
   * \brief Get the value of the adjoint solution in the previous BGS subiteration.
   * \param[out] val_solution - adjoint solution in the previous BGS subiteration.
   */
  inline su2double Get_BGSSolution_k(Idx_t iPoint, Idx_t iDim) const { return Solution_BGS_k(iPoint,iDim);}

  /*!
   * \brief Set the value of the adjoint geometry solution in the previous BGS subiteration.
   */
  inline void Set_BGSSolution_Geometry(Idx_t iPoint) {
    for (Idx_t iDim = 0; iDim < nDim; iDim++)
      Solution_Geometry_BGS_k(iPoint,iDim) = Solution_Geometry(iPoint,iDim);
  }

  /*!
   * \brief Get the value of the adjoint geometry solution in the previous BGS subiteration.
   * \param[out] val_solution - geometrical adjoint solution in the previous BGS subiteration.
   */
  inline su2double Get_BGSSolution_Geometry(Idx_t iPoint, Idx_t iDim) const {
    return Solution_Geometry_BGS_k(iPoint,iDim);
  }

  /*!
   * \brief Set the contribution of crossed terms into the derivative.
   */
  inline void SetCross_Term_Derivative(Idx_t iPoint, Idx_t iVar, su2double der) {
    Cross_Term_Derivative(iPoint,iVar) = der;
  }

  /*!
   * \brief Get the contribution of crossed terms into the derivative.
   */
  inline su2double GetCross_Term_Derivative(Idx_t iPoint, Idx_t iVar) const {
    return Cross_Term_Derivative(iPoint,iVar);
  }

};
