July 21, 2018 14:40:07 Library.fmp12 - helpReferenceTagFindReferenceRecord -1-
help: reference: helpReferenceTagFindReferenceRecord
#
#
#Send general layout name and help column
#number to the help script so it can take the
#user to help for this layout and column.
Set Variable [ $$helpLayoutName; Value:"Reference" ]
#
#Send user to help column.
Set Variable [ $$helpColumnName; Value:"H" ]
Perform Script [ “help” ]
#
#
