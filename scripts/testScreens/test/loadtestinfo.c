testScreens: test: loadtestinfo
#
#This first section is key to stopping this script
#when another script for example loops thru
#many records each of which would trigger this
#script and really slow down the program and
#create strobe effect that is really irritating to
#look at.
If [ $$stoploadtestinfo = 1 ]
Exit Script [ ]
End If
#
#This key effects the conditional formatting
Set Variable [ $$RecordID; Value:Get (RecordID) ]
Go to Field [ ]
Refresh Window
January 7, 平成26 12:23:59 Imagination Quality Management.fp7 - loadtestinfo -1-
