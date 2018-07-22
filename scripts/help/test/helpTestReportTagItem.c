July 21, 2018 14:43:55 Library.fmp12 - helpTestReportTagItem -1-
help: test: helpTestReportTagItem
#
#
#Send general layout name and help column
#number to the help script so it can take the
#user to help for this layout and column.
Set Variable [ $$helpLayoutName; Value:"Test" ]
Set Variable [ $$helpColumnName; Value:"F" ]
Perform Script [ “help” ]
#
#
