July 21, 2018 14:40:48 Library.fmp12 - helpSetupTestEdit -1-
help: setup: helpSetupTestEdit
#
#
#Send general layout name and help column
#number to the help script so it can take the
#user to help for this layout and column.
Set Variable [ $$helpLayoutName; Value:"Setup" ]
Set Variable [ $$helpColumnName; Value:"D" ]
Perform Script [ “help (update)” ]
#
#
