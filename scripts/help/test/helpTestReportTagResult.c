July 21, 2018 14:43:44 Library.fmp12 - helpTestReportTagResult -1-
help: test: helpTestReportTagResult
#
#
#Send general layout name and help column
#number to the help script so it can take the
#user to help for this layout and column.
Set Variable [ $$helpLayoutName; Value:"Test" ]
Set Variable [ $$helpColumnName; Value:"E" ]
Perform Script [ “help” ]
#
#
