July 21, 2018 14:44:05 Library.fmp12 - helpTestReportTagInfo -1-
help: test: helpTestReportTagInfo
#
#
#Send general layout name and help column
#number to the help script so it can take the
#user to help for this layout and column.
Set Variable [ $$helpLayoutName; Value:"Test" ]
Set Variable [ $$helpColumnName; Value:"G" ]
Perform Script [ “help” ]
#
#
