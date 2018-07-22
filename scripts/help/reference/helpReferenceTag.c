July 21, 2018 14:39:47 Library.fmp12 - helpReferenceTag -1-
help: reference: helpReferenceTag
#
#
#Send general layout name and help column
#number to the help script so it can take the
#user to help for this layout and column.
Set Variable [ $$helpLayoutName; Value:"Reference" ]
#
#Send user to help column.
If [ $$citationMatch = "node" ]
Set Variable [ $$helpColumnName; Value:"D" ]
Else If [ $$citationMatch = "copyright" ]
Set Variable [ $$helpColumnName; Value:"E" ]
Else If [ $$citationMatch = "cite" ]
Set Variable [ $$helpColumnName; Value:"G" ]
Else
Set Variable [ $$helpColumnName; Value:"F" ]
End If
Perform Script [ “help” ]
#
#
