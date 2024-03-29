//=--ConstraintBuilder.h------------------------------------------*- C++-*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_CheckMate_CONSTRAINTBUILDER_H
#define LLVM_CLANG_CheckMate_CONSTRAINTBUILDER_H

#include "clang/CheckMate/ProgramInfo.h"
#include "clang/AST/ASTConsumer.h"

// First step in generating initial constraints is to collect functions
// and variables the need to be analysed. This will also merge
// function definitions together.
// Atleast as of now, here we intend to collect functions that are marked as Tainted
class VariableAdderConsumer : public clang::ASTConsumer {
public:
  explicit VariableAdderConsumer(ProgramInfo &I, clang::ASTContext *C)
      : Info(I) {}

  void HandleTranslationUnit(clang::ASTContext &) override;

private:
  ProgramInfo &Info;
};

// Final step in generating initial constraints is to scan type variables and
// function bodies for relationships that generate the constraints.
class ConstraintBuilderConsumer : public clang::ASTConsumer {
public:
  explicit ConstraintBuilderConsumer(ProgramInfo &I, clang::ASTContext *C)
      : Info(I) {}

  void HandleTranslationUnit(clang::ASTContext &) override;

private:
  ProgramInfo &Info;
};

#endif
