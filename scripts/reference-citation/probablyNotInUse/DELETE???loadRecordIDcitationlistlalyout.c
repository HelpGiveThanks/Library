reference(citation): probablyNotInUse: DELETE???loadRecordIDcitationlistlalyout
#REMOVED it from use after it kept resetting ID number and messing up text formatting on main TL window. It does not seem to be needed for an calc, but not sure entirely so have not deleted it yet.
#This first section is key to stopping this script
#when another script for example loops thru
#many records each of which would trigger this
#script and really slow down the program and
#create strobe effect that is really irritating to
#look at.
If [ $$stoploadCitation = 1 ]
Exit Script [ ]
End If
Set Variable [ $$recordID; Value:Get (RecordID) ]
Refresh Window
January 7, 平成26 18:03:07 Imagination Quality Management.fp7 - DELETE???loadRecordIDcitationlistlalyout -1-
