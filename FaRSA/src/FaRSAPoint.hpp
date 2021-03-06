// Copyright (C) 2020 Frank E. Curtis, Daniel P. Robinson
//
// This code is published under the ??? License.
//
// Author(s) : Frank E. Curtis, Daniel P. Robinson

#ifndef __FARSAPOINT_HPP__
#define __FARSAPOINT_HPP__

#include <memory>
#include <string>

#include "FaRSADeclarations.hpp"
#include "FaRSAProblem.hpp"
#include "FaRSAQuantities.hpp"
#include "FaRSAReporter.hpp"
#include "FaRSAVector.hpp"

namespace FaRSA
{

/**
 * Forward declarations
 */
class Quantities;
class Problem;
class Reporter;
class Vector;

/**
 * Point class
 */
class Point
{

public:
  /** @name Constructors */
  //@{
  /**
   * Construct Point
   * \param[in] problem is pointer to Problem object
   * \param[in] vector is pointer to Vector object
   * \param[in] scale is scaling factor for function evaluations
   */
  Point(const std::shared_ptr<Problem> problem,
        const std::shared_ptr<Vector> vector,
        double scale);
  //@}

  /** @name Destructor */
  //@{
  /**
   * Delete data
   */
  ~Point(){};
  //@}

  /** @name Print methods */
  //@{
  /**
   * Print data
   * \param[in] reporter is pointer to Reporter object from FaRSA
   * \param[in] name is name of point to print
   */
  void print(const Reporter* reporter,
             std::string name) const;
  //@}

  /** @name Make-new methods */
  //@{
  /**
   * Make new Point by adding "scalar1" times this Point's Vector to "scalar2" times other_vector
   * \param[in] scalar1 is scalar value for linear combination
   * \param[in] scalar2 is scalar value for linear combination
   * \param[in] other_vector is reference to other Vector
   * \return pointer to new Point
   */
  std::shared_ptr<Point> makeNewLinearCombination(double scalar1,
                                                  double scalar2,
                                                  const Vector& other_vector) const;
  //@}

  /** @name Set methods */
  //@{
  /**
   * Determine scale for objective function
   * \param[in,out] quantities is reference to IterationQuanitites object from FaRSA
   * \return boolean indicating success
   */
  void determineScale(Quantities& quantities);
  /**
   * Evaluate objective
   * \param[in,out] quantities is reference to IterationQuanitites object from FaRSA
   * \return boolean indicating success
   */
  bool evaluateObjective(Quantities& quantities);
  /**
   * Evaluate gradient
   * \param[in,out] quantities is reference to IterationQuanitites object from FaRSA
   * \return boolean indicating success
   */
  bool evaluateGradient(Quantities& quantities);
  /**
   * Scale objective
   */
  void scaleObjective()
  {
    ASSERT_EXCEPTION(objective_evaluated_, FARSA_FUNCTION_EVALUATION_ASSERT_EXCEPTION, "Objective should have been evaluated, but wasn't.");
    objective_ *= scale_;
  }
  /**
   * Scale gradient
   */
  void scaleGradient()
  {
    ASSERT_EXCEPTION(gradient_evaluated_, FARSA_GRADIENT_EVALUATION_ASSERT_EXCEPTION, "Gradient should have been evaluated, but wasn't.");
    gradient_->scale(scale_);
  };
  //@}

  /** @name Get methods */
  //@{
  /**
   * Get pointer to Problem
   * \return is pointer to Problem corresponding to point
   */
  inline std::shared_ptr<Problem> problem() const { return problem_; };
  /**
   * Get pointer to vector
   * \return is pointer to Vector defining point
   */
  inline std::shared_ptr<Vector> vector() const { return vector_; };
  /**
   * Get objective
   * \return objective as double
   */
  inline double objective() const
  {
    ASSERT_EXCEPTION(objective_evaluated_, FARSA_FUNCTION_EVALUATION_ASSERT_EXCEPTION, "Function should have been evaluated, but wasn't.");
    return objective_;
  };
  /**
   * Get objective (unscaled)
   * \return objective (unscaled) as double
   */
  inline double objectiveUnscaled() const
  {
    ASSERT_EXCEPTION(objective_evaluated_, FARSA_FUNCTION_EVALUATION_ASSERT_EXCEPTION, "Function should have been evaluated, but wasn't.");
    return objective_ / scale_;
  };
  /**
   * Get pointer to gradient
   * \return gradient as pointer to Vector
   */
  inline std::shared_ptr<Vector> gradient() const
  {
    ASSERT_EXCEPTION(gradient_evaluated_, FARSA_GRADIENT_EVALUATION_ASSERT_EXCEPTION, "Gradient should have been evaluated, but wasn't.");
    return gradient_;
  };
  /**
   * Get scale
   * \return is scale factor
   */
  inline double scale() const { return scale_; };
  //@}

private:
  /** @name Default compiler generated methods
   * (Hidden to avoid implicit creation/calling.)
   */
  //@{
  /**
   * Copy constructor
   */
  Point(const Point&);
  /**
   * Overloaded equals operator
   */
  void operator=(const Point&);
  //@}

  /** @name Private members */
  //@{
  bool objective_evaluated_;
  bool gradient_evaluated_;
  double objective_;
  double scale_;
  std::shared_ptr<Problem> problem_;
  std::shared_ptr<Vector> vector_;
  std::shared_ptr<Vector> gradient_;
  //@}

}; // end Point

} // namespace FaRSA

#endif /* __FARSAPOINT_HPP__ */
