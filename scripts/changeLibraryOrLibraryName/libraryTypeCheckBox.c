changeLibraryOrLibraryName: libraryTypeCheckBox
#
#Exit the checkbox.
Go to Field [ ]
#
#Set default layouts for a reference library.
If [ tempSetup::InventoryLibaryYN = "" ]
Set Field [ tempSetup::layoutLtagK; "" ]
Set Field [ tempSetup::layoutRtagK; "" ]
Set Field [ tempSetup::layoutLtagN; "" ]
Set Field [ tempSetup::layoutRtagN; "" ]
#
#Designate library as a reference library.
Set Field [ sectionAttributionInfo::order; "" ]
Else
#
#Set default layouts for a stuff/inventory library.
Set Field [ tempSetup::layoutLtagK; "moreltagNKs2" ]
Set Field [ tempSetup::layoutRtagK; "moreReferenceMenu2SkeywordOrNode1" ]
Set Field [ tempSetup::layoutLtagN; "moreltagNKs2" ]
Set Field [ tempSetup::layoutRtagN; "moreReferenceMenu2SkeywordOrNode1" ]
#
#Designate library as a stuff/inventory library.
Set Field [ sectionAttributionInfo::order; 1 ]
End If
December 27, ଘ౮27 19:05:50 Library.fp7 - libraryTypeCheckBox -1-
