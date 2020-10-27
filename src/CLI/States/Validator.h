//
// Created by Rodion Shyshkin on 27.10.2020.
//

#ifndef TODOLIST_SRC_CLI_STATES_VALIDATOR_H_
#define TODOLIST_SRC_CLI_STATES_VALIDATOR_H_

#include <string>
#include <boost/date_time/gregorian/greg_date.hpp>
#include <optional>
#include <boost/date_time/gregorian/parsers.hpp>
#include <API/Priority.h>
#include <iostream>

/*
 * \brief Toolkit for validating & parsing parameters.
 *
 * @author Rodion Shyshkin
 */

namespace validator {
  static std::optional <boost::gregorian::date> ParseDate(const std::string& param) {
    try{
      boost::gregorian::date result;
      if(param.empty()) result = boost::gregorian::date{boost::gregorian::not_a_date_time};
      else result = boost::gregorian::from_string(param);
      return std::make_optional<boost::gregorian::date>(result);
    }
    catch(const std::out_of_range&) {
      return std::nullopt;
    }
    catch(const std::invalid_argument&) {
      return std::nullopt;
    }
    catch(const boost::bad_lexical_cast&) {
      return std::nullopt;
    }
  }

  static std::optional<unsigned int> ParseID(const std::string& param) {
    unsigned int result;
    try {
      result = std::stoul(param);
    }
    catch(const std::invalid_argument&) {
      return std::nullopt;
    }
    catch(const std::out_of_range&) {
      return std::nullopt;
    }
    return result;
  }

  static std::optional<bool> ParseBoolFlag(const std::string& param) {
    if(param == "y" || param == "yes") return true;
    else if(param == "n" || param == "no") return false;
    else return std::nullopt;
  }

  static std::optional<Priority> ParsePriority(const std::string& param) {
    if(param.empty()) return Priority::EMPTY;
    else if(param == "Low") return Priority::LOW;
    else if(param == "Medium") return Priority::MEDIUM;
    else if(param == "High") return Priority::HIGH;
    else return std::nullopt;
  }

  static bool ValidateName(const std::string& param) {
    return !param.empty();
  }

  static bool ValidateFilename(const std::string& param) {
    return !param.empty();
  }
}

#endif //TODOLIST_SRC_CLI_STATES_VALIDATOR_H_
