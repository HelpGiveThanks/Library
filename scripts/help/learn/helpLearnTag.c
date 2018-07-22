July 21, 2018 14:38:41 Library.fmp12 - helpLearnTag  -1-
help: learn: helpLearnTag
#
#
#Send general layout name and help column
#number to the help script so it can take the
#user to help for this layout and column.
Set Variable [ $$helpLayoutName; Value:"Learn" ]
#
#Send user to idea or inventory help column.
If [ TEMP::InventoryLibraryYN = "" ]
Set Variable [ $$helpColumnName; Value:"E" ]
Else
Set Variable [ $$helpColumnName; Value:"F" ]
End If
Perform Script [ “help (update)” ]
#
#
