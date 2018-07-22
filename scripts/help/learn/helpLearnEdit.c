July 21, 2018 14:37:39 Library.fmp12 - helpLearnEdit -1-
help: learn: helpLearnEdit
#
#
#Send general layout name and help column
#number to the help script so it can take the
#user to help for this layout and column.
Set Variable [ $$helpLayoutName; Value:"Learn" ]
Set Variable [ $$helpColumnName; Value:"B" ]
Perform Script [ “help” ]
#
#
