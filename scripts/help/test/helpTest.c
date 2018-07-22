July 21, 2018 14:43:21 Library.fmp12 - helpTest -1-
help: test: helpTest
#
#
#Send general layout name and help column
#number to the help script so it can take the
#user to help for this layout and column.
Set Variable [ $$helpLayoutName; Value:"Test" ]
Set Variable [ $$helpColumnName; Value:"C" ]
Perform Script [ “help” ]
#
#
