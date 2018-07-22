July 21, 2018 14:43:33 Library.fmp12 - helpTestReportMain -1-
help: test: helpTestReportMain
#
#
#Send general layout name and help column
#number to the help script so it can take the
#user to help for this layout and column.
Set Variable [ $$helpLayoutName; Value:"Test" ]
Set Variable [ $$helpColumnName; Value:"D" ]
Perform Script [ “help” ]
#
#
