July 21, 2018 14:17:59 Library.fmp12 - sortButtonLearnLayouts -1-
tagMenu: sortButtonLearnLayouts
#
#Perform script for brainstorm and test tags only.
If [ $$citationMatch = "brainstorm" and $$findMode = "" or
$$citationmatch = "test" and $$findMode = "" or
$$citationmatch = "testResult" and $$findMode = "" or
Right ( Get (LayoutName) ; 4 ) = "Info" ]
#
#If current sort is by date, then sort records by
#order number.
If [ TEMP::TLTestSort = "" and $$citationMatch = "test"
 or
TEMP::TLTestSort = "" and $$citationMatch = "testResult"
 or
TEMP::TLTestSort = "" and Right ( Get (LayoutName) ; 4 ) = "Info" ]
#
#Sort button script uses 1 to tell
#it to perform the next sort by date instead of
#by order number which is the default sort.
Set Field [ TEMP::TLTestSort; 1 ]
If [ Right ( Get (LayoutName) ; 4 ) = "info" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearnReportTags::orderTestInformation; based
on value list: “testPulldownListANDsortOrderList”
testlearnReportTags::timestamp; descending ]
[ Restore; No dialog ]
Exit Script [ ]
Else If [ $$citationMatch = "testResult" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearnReportTags::orderTestResult; based on
value list: “testPulldownListANDsortOrderList”
testlearnReportTags::timestamp; descending ]
[ Restore; No dialog ]
Exit Script [ ]
End If
Perform Script [ “sortTestOrBrainstormTaggedLearnRecords” ]
Exit Script [ ]
Else If [ TEMP::TLBrainstormSort = "" and $$citationMatch = "brainstorm" ]
Set Field [ TEMP::TLBrainstormSort; 1 ]
Perform Script [ “sortTestOrBrainstormTaggedLearnRecords” ]
Exit Script [ ]
End If
Set Field [ TEMP::TLTestSort; "" ]
#
#Sort the records by date field, if current sort is
#by order number.
If [ Right ( Get (LayoutName) ; 4 ) = "info"
 or
$$citationMatch = "brainstorm"
 or
$$citationMatch = "test"
 or
$$citationMatch = "testResult" ]
#
#Sort the records by order field.
If [ Get (LayoutTableName ) = "testLearnReportTags" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearnReportTags::date; descending
testlearnReportTags::timestamp; descending ]
[ Restore; No dialog ]
Else
If [ TEMP::InventoryLibraryYN = "" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
Else
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::orderInventoryGroupNumber; based
on value list: “testPulldownListANDsortOrderList”
testlearn::note; ascending ]
[ Restore; No dialog ]
End If
End If
End If
#
#Set the sort preference field to date.
If [ $$citationMatch = "brainstorm" ]
Set Field [ TEMP::TLBrainstormSort; "" ]
Else If [ $$citationMatch = "test"
 or
$$citationMatch = "testResult" ]
Set Field [ TEMP::TLTestSort; "" ]
End If
#
End If
