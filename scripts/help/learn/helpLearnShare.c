July 21, 2018 14:38:27 Library.fmp12 - helpLearnShare -1-
help: learn: helpLearnShare
#
#
#Send general layout name and help column
#number to the help script so it can take the
#user to help for this layout and column.
Set Variable [ $$helpLayoutName; Value:"Learn" ]
Set Variable [ $$helpColumnName; Value:"D" ]
Perform Script [ “help (update)” ]
#
#
