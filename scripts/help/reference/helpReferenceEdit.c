July 21, 2018 14:39:15 Library.fmp12 - helpReferenceEdit -1-
help: reference: helpReferenceEdit
#
#
#Send general layout name and help column
#number to the help script so it can take the
#user to help for this layout and column.
Set Variable [ $$helpLayoutName; Value:"Reference" ]
Set Variable [ $$helpColumnName; Value:"B" ]
Perform Script [ “help” ]
#
#
