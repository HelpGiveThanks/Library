July 21, 2018 14:41:01 Library.fmp12 - helpSetupMain -1-
help: setup: helpSetupMain
#
#
#Send general layout name and help column
#number to the help script so it can take the
#user to help for this layout and column.
Set Variable [ $$helpLayoutName; Value:"Setup" ]
Set Variable [ $$helpColumnName; Value:"A" ]
Perform Script [ “help” ]
#
#
