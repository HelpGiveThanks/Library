tagMenu: ChangeTLRecordsSort_Button
#
#Perform script for sample and test tags only.
If [ $$citationMatch = "sample" and $$ﬁndMode = "" or
$$citationmatch = "test" and $$ﬁndMode = "" ]
#
#If current sort is by date, then sort records by
#order number.
If [ TEMP::TLTestSort = "" and $$citationMatch = "test" ]
Set Field [ TEMP::TLTestSort; "order" ]
Perform Script [ “SortTLRecordsByOrderNumber” ]
Exit Script [ ]
Else If [ TEMP::TLSampleSort = "" and $$citationMatch = "sample" ]
Set Field [ TEMP::TLSampleSort; "order" ]
Perform Script [ “SortTLRecordsByOrderNumber” ]
Exit Script [ ]
End If
Set Field [ TEMP::TLTestSort; "" ]
#
#Sort the records by date ﬁeld, if current sort is
#by order number.
Sort Records [ Speciﬁed Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
#
#Set the sort preference ﬁeld to date.
If [ $$citationMatch = "sample" ]
Set Field [ TEMP::TLSampleSort; "" ]
Else If [ $$citationMatch = "test" ]
Set Field [ TEMP::TLTestSort; "" ]
End If
#
End If
January 7, 平成26 16:49:07 Imagination Quality Management.fp7 - ChangeTLRecordsSort_Button -1-
