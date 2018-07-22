July 21, 2018 14:41:57 Library.fmp12 - helpSetupTagNode -1-
help: setup: helpSetupTagNode
#
#
#Send general layout name and help column
#number to the help script so it can take the
#user to help for this layout and column.
Set Variable [ $$helpLayoutName; Value:"Setup" ]
#
#Send user to help column.
Set Variable [ $$helpColumnName; Value:"F" ]
Perform Script [ “help (update)” ]
#
#
