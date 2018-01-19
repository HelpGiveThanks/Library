January 15, 2018 17:11:06 Library.fmp12 - defaultsAll -1-
tagMenu: defaultsAll
#
#Make sure window to fills half of the screen.
Move/Resize Window [ Current Window; Height: Get (ScreenHeight); Width: Get (ScreenWidth) / 2; Top: 0; Left: Get (ScreenWidth) /
2 ]
#
#Go the defaults layout.
Set Variable [ $$stopAddTagToCitation; Value:1 ]
Go to Layout [ “defaultsAll” (tempSetup) ]
Set Variable [ $$stopAddTagToCitation ]
#
#Delete all records as user could have
#performed some scripts that created multiple
#temporary records to show them information
#about records that require attention.
Show All Records
Delete All Records
[ No dialog ]
#
#Create a new default record to show current
#selected default tags and library information.
New Record/Request
#
#Insure that correct filename is shown.
#For some reason, FileMaker will not calculate
#accurate filename unless a second new
#record is created and then the previous
#record is deleted.
New Record/Request
Go to Record/Request/Page
[ Previous ]
Delete Record/Request
[ No dialog ]
#
Set Variable [ $$citationMatch ]
Refresh Window
#
