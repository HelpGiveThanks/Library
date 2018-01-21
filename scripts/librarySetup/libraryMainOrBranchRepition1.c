January 11, 2018 19:26:31 Library.fmp12 - libraryMainOrBranchRepition1 -1-
librarySetup: libraryMainOrBranchRepition1
#
#Exit the checkbox.
Go to Field [ ]
#
If [ TEMP::userLibraryMainOrBranch[1] = "" ]
#
#Designate library as a reference library.
Set Field [ TEMP::userLibraryMainOrBranch[2]; 1 ]
#
Else
#
#Designate library as branch library.
Set Field [ TEMP::userLibraryMainOrBranch[2]; "" ]
#
End If
