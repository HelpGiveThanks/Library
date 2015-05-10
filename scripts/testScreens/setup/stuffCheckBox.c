testScreens: setup: stuffCheckBox
Go to Field [ ]
If [ tempSetup::InventoryLibaryYN = "" ]
Set Field [ tempSetup::layoutLtagK; "" ]
Set Field [ tempSetup::layoutRtagK; "" ]
Set Field [ tempSetup::layoutLtagN; "" ]
Set Field [ tempSetup::layoutRtagN; "" ]
Else
Set Field [ tempSetup::layoutLtagK; "moreltagNKs2" ]
Set Field [ tempSetup::layoutRtagK; "moreReferenceMenu2SkeywordOrNode1" ]
Set Field [ tempSetup::layoutLtagN; "moreltagNKs2" ]
Set Field [ tempSetup::layoutRtagN; "moreReferenceMenu2SkeywordOrNode1" ]
End If
May 4, 平成27 21:28:07 Library.fp7 - stuffCheckBox -1-
