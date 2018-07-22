July 21, 2018 14:41:34 Library.fmp12 - helpSetupTagCopyright -1-
help: setup: helpSetupTagCopyright
#
#
#Send general layout name and help column
#number to the help script so it can take the
#user to help for this layout and column.
Set Variable [ $$helpLayoutName; Value:"Setup" ]
#
#Send user to help column.
Set Variable [ $$helpColumnName; Value:"G" ]
Perform Script [ “help (update)” ]
#
#
