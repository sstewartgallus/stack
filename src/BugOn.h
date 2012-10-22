#include <llvm/IRBuilder.h>
#include <llvm/Pass.h>

llvm::Function *getBugOn(llvm::Module *);
llvm::Function *getOrInsertBugOn(llvm::Module *);

struct BugOnPass : llvm::FunctionPass {
	BugOnPass(char &ID) : llvm::FunctionPass(ID), BugOn(NULL) {}

	virtual void getAnalysisUsage(llvm::AnalysisUsage &) const;
	virtual bool runOnFunction(llvm::Function &);

protected:
	typedef BugOnPass super;
	typedef llvm::IRBuilder<> BuilderTy;
	BuilderTy *Builder;

	virtual bool visit(llvm::Instruction *) = 0;

	bool insert(llvm::Value *, const char *Bug);
	llvm::Module *getModule();

private:
	llvm::Function *BugOn;
	unsigned int MD_bug;
};