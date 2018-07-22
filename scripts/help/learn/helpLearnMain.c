July 21, 2018 14:38:04 Library.fmp12 - helpLearnMain -1-
help: learn: helpLearnMain
#
#
#Send general layout name and help column
#number to the help script so it can take the
#user to help for this layout and column.
Set Variable [ $$helpLayoutName; Value:"Learn" ]
Set Variable [ $$helpColumnName; Value:"A" ]
Perform Script [ “help (update)” ]
#
#
