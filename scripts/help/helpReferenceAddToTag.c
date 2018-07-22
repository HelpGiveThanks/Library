July 20, 2018 17:16:23 Library.fmp12 - helpReferenceAddToTag -1-
help: helpReferenceAddToTag
#
#
#Send general layout name and help column
#number to the help script so it can take the
#user to help for this layout and column.
Set Variable [ $$helpLayoutName; Value:"Reference" ]
#
#Send user to help column.
Set Variable [ $$helpColumnName; Value:"A" ]
Perform Script [ “help (update)” ]
#
#
