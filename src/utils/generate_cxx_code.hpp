/******************************************************************************
 *                                                                            *
 *    Copyright 2020   Lawrence Livermore National Security, LLC and other    *
 *    Whole Cell Simulator Project Developers. See the top-level COPYRIGHT    *
 *    file for details.                                                       *
 *                                                                            *
 *    SPDX-License-Identifier: MIT                                            *
 *                                                                            *
 ******************************************************************************/

#ifndef  __WCS_UTILS_GENERATE_CXX_CODE__
#define  __WCS_UTILS_GENERATE_CXX_CODE__

#if defined(WCS_HAS_CONFIG)
#include "wcs_config.hpp"
#else
#error "no config"
#endif

#include <unordered_map>
#include <set>
#include "sbml_utils.hpp"
#include <cstdio>

#if defined(WCS_HAS_SBML)
#include <sbml/SBMLTypes.h>
#include <sbml/common/extern.h>

LIBSBML_CPP_NAMESPACE_USE

namespace wcs {
/** \addtogroup wcs_utils
 *  @{ */

class generate_cxx_code {
 public:
  using map_symbol_to_ast_node_t
  = std::unordered_map <std::string, const LIBSBML_CPP_NAMESPACE::ASTNode *>;
  using params_map_t = std::unordered_map <std::string, std::vector<std::string>>;
  using rate_rules_dep_t = std::unordered_map <std::string, std::set<std::string>>;
  using event_assignments_t = std::unordered_set<std::string>;
  using initial_assignments_t = map_symbol_to_ast_node_t;
  using assignment_rules_t = map_symbol_to_ast_node_t;
  using model_reactions_t = map_symbol_to_ast_node_t;
  using rate_rules_t = map_symbol_to_ast_node_t;
  using constant_init_ass_t = map_symbol_to_ast_node_t;

  static const std::string generate_code(const LIBSBML_CPP_NAMESPACE::Model& model,
  params_map_t& dep_params_f,
  params_map_t& dep_params_nf,
  rate_rules_dep_t& rate_rules_dep_map);
  static const std::string compile_code(const std::string generated_filename);

  template <typename TTT>
  class basetype_to_string {
   public:
    static const char* value;
  };

 private:
  static void get_dependencies(
    const LIBSBML_CPP_NAMESPACE::ASTNode& math,
    std::vector<std::string> & math_elements,
    const std::unordered_set<std::string> & good,
    const map_symbol_to_ast_node_t & constant_init_assig,
    const map_symbol_to_ast_node_t & variables_assig_rul,
    const map_symbol_to_ast_node_t & model_reactions_s,
    const std::unordered_set<std::string> & local_params);

  static std::vector<std::string> get_all_dependencies(
    const LIBSBML_CPP_NAMESPACE::ASTNode& formula,
    const std::unordered_set<std::string> & good,
    const map_symbol_to_ast_node_t & constant_init_assig,
    const map_symbol_to_ast_node_t & variables_assig_rul,
    const map_symbol_to_ast_node_t & model_reactions_s,
    const std::unordered_set<std::string> & local_params);

  static void return_denominators(
    const LIBSBML_CPP_NAMESPACE::ASTNode& formula,
    std::vector<std::string> & denominators,
    const std::string& reaction_name);
  static std::vector<std::string> return_all_denominators(
    const LIBSBML_CPP_NAMESPACE::ASTNode& formula,
    const std::string& reaction_name);

  static void find_used_params(
  const LIBSBML_CPP_NAMESPACE::Model& model,
  std::unordered_set <std::string>& used_params,
  const initial_assignments_t& sinitial_assignments,
  const assignment_rules_t& assignment_rules_map,
  const model_reactions_t& model_reactions_map,
  const rate_rules_t& rate_rules_map,
  const std::unordered_set <std::string>& model_species,
  const event_assignments_t& m_ev_assig);

  static void print_constants_and_initial_states(
  const LIBSBML_CPP_NAMESPACE::Model& model,
  const char * Real,
  std::ofstream & genfile,
  map_symbol_to_ast_node_t & sconstant_init_assig,
  const initial_assignments_t& sinitial_assignments,
  const assignment_rules_t& assignment_rules_map,
  const std::unordered_set <std::string>& used_params,
  std::unordered_set <std::string>& good_params,
  const model_reactions_t & model_reactions_map,
  const rate_rules_t& rate_rules_map,
  std::unordered_set<std::string>& wcs_all_const,
  std::unordered_set<std::string>& wcs_all_var,
  const event_assignments_t& m_ev_assig);

  static void print_functions(
  const LIBSBML_CPP_NAMESPACE::Model& model,
  const char * Real,
  std::ofstream & genfile);

  static void print_event_functions(
  const LIBSBML_CPP_NAMESPACE::Model& model,
  const char * Real,
  std::ofstream & genfile,
  const event_assignments_t & m_ev_assig,
  const std::unordered_set<std::string>& wcs_all_const,
  const std::unordered_set<std::string>& wcs_all_var);

  static void print_global_state_functions(
  const LIBSBML_CPP_NAMESPACE::Model& model,
  const char * Real,
  std::ofstream & genfile,
  const std::unordered_set<std::string> & good_params,
  const map_symbol_to_ast_node_t & sconstant_init_assig,
  const assignment_rules_t & assignment_rules_map,
  const model_reactions_t & model_reactions_map,
  const std::unordered_set<std::string>& wcs_all_const,
  const std::unordered_set<std::string>& wcs_all_var);

  static void print_reaction_rates(
  const LIBSBML_CPP_NAMESPACE::Model& model,
  const char * Real,
  std::ofstream & genfile,
  const std::unordered_set<std::string> & good_params,
  const map_symbol_to_ast_node_t & sconstant_init_assig,
  const assignment_rules_t & assignment_rules_map,
  const model_reactions_t & model_reactions_map,
  const event_assignments_t & m_ev_assig,
  const std::unordered_set<std::string>& wcs_all_const,
  const std::unordered_set<std::string>& wcs_all_var,
  params_map_t& dep_params_f,
  params_map_t& dep_params_nf,
  const rate_rules_dep_t& rate_rules_dep_map);

};

/**@}*/
} // end of namespace wcs
#endif // defined(WCS_HAS_SBML)
#endif //  __WCS_UTILS_GENERATE_CXX_CODE__