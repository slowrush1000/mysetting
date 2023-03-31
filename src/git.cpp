
#include "git.hpp"

my::Git::~Git()
{
}

std::string 
my::Git::getGitBranch()
{
    return kGitBranch;
}

std::string  
my::Git::getGitCommitHash()
{
    return kGitCommitHash;
}
