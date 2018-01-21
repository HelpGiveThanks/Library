January 19, 2018 1:23:58 Library.fmp12 - helpBack -1-
help: helpBack
#
#This script functions like a browsers back button
#script, taking users back thru help windows bread
#crumb style.
If [ ValueCount ( tempSetup::helpName ) = 1 ]
Exit Script [ ]
Else
Set Variable [ $value1; Value:GetValue ( tempSetup::helpName ; ValueCount ( tempSetup::helpName ) ) ]
Set Field [ tempSetup::helpName; Substitute ( $value1 ; tempSetup::helpName ; "" &¶ ) ]
Set Variable [ $value1; Value:GetValue ( tempSetup::helpName ; 1 ) ]
Go to Layout [ $value1 ]
End If
