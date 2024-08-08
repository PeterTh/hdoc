// Copyright 2019-2023 hdoc
// SPDX-License-Identifier: AGPL-3.0-only

#pragma once

#include "ctml.hpp"
#include "llvm/Support/ThreadPool.h"

#include "types/Config.hpp"
#include "types/Index.hpp"

namespace hdoc {
namespace serde {

/// @brief Serialize hdoc's index to HTML files
class HTMLWriter {
public:
  HTMLWriter(const hdoc::types::Index* index, const hdoc::types::Config* cfg, llvm::ThreadPool& pool);
  void printFunctions() const;
  void printAliases() const;
  void printRecords() const;
  void printRecord(const hdoc::types::RecordSymbol& c) const;
  void printNamespaces() const;
  void printEnums() const;
  void printEnum(const hdoc::types::EnumSymbol& e) const;

  /// @brief Print the search page for the documentation
  void printSearchPage() const;

  /// @brief Print the index.html page for the documentation
  void printProjectIndex() const;

  /// @brief Convert Markdown files to HTML and save them to the filesystem
  void processMarkdownFiles() const;

private:
  const hdoc::types::Index*  index;
  const hdoc::types::Config* cfg;
  llvm::ThreadPool&          pool;

  void printFunction(const hdoc::types::FunctionSymbol& f,
                     CTML::Node&                        main,
                     const std::string_view             gitRepoURL,
                     const std::string_view             gitDefaultBranch) const;

  CTML::Node printNamespace(const hdoc::types::NamespaceSymbol& ns) const;

  /// @brief Get a string representation of a namespace that can be used in a URL (i.e. replace '::' with '_')
  std::string getNamespaceString(const hdoc::types::SymbolID& n) const;

  // @brief Get the URL for a given symbol
  std::string getFunctionURL(const hdoc::types::SymbolID& f, bool relative) const;
  std::string getFunctionGroupURL(const hdoc::types::FreestandingFunctionID& f, bool relative) const;
  
  std::string getHyperlinkedFunctionProto(const std::string_view proto, const hdoc::types::FunctionSymbol& f) const;
};
std::string clangFormat(const std::string_view s, const uint64_t& columnLimit = 50);
std::string getBareTypeName(const std::string_view typeName);
} // namespace serde
} // namespace hdoc
