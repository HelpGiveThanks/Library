July 21, 2018 14:43:06 Library.fmp12 - helpSetupTest -1-
help: test: helpSetupTest
#
#
#Send general layout name and help column
#number to the help script so it can take the
#user to help for this layout and column.
Set Variable [ $$helpLayoutName; Value:"Test" ]
Set Variable [ $$helpColumnName; Value:"B" ]
Perform Script [ “help” ]
#
#
