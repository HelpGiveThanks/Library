January 10, 2018 15:20:43 Library.fmp12 - nextLayout -1-
dataCleanUpScripts: nextLayout
#
#Use this script to go the next layout to test if
#it is in list view or table view.
Set Variable [ $$stoploadCitation; Value:1 ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
#
If [ $$nextLayout = "" ]
Set Variable [ $$nextLayout; Value:1 ]
End If
#
Go to Layout [ $$nextLayout ]
#
Set Variable [ $$nextLayout; Value:$$nextLayout + 1 ]
Show/Hide Toolbars
[ Show ]
Install Menu Set [ “[Standard FileMaker Menus]” ]
