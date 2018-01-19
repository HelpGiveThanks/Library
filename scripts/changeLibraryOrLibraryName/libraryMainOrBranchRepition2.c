January 11, 2018 19:28:58 Library.fmp12 - libraryMainOrBranchRepition2 -1-
librarySetup: libraryMainOrBranchRepition2
#
#Exit the checkbox.
Go to Field [ ]
#
If [ tempSetup::userLibraryMainOrBranch[2] = 1 ]
#
#Designate library as a reference library.
Set Field [ TEMP::userLibraryMainOrBranch; "" ]
#
Else
#
#Designate library as a stuff/inventory library.
Set Field [ TEMP::userLibraryMainOrBranch; 1 ]
#
End If
