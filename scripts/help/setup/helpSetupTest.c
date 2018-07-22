July 21, 2018 14:40:29 Library.fmp12 - helpSetupTest -1-
help: setup: helpSetupTest
#
#
#Send general layout name and help column
#number to the help script so it can take the
#user to help for this layout and column.
Set Variable [ $$helpLayoutName; Value:"Setup" ]
Set Variable [ $$helpColumnName; Value:"C" ]
Perform Script [ “help (update)” ]
#
#
