tagMenu: probablyNotInUse: loadItemRecordForLearnTagMenuDELETE!!!
#Capture recordID to conditionally format current record.
If [ $$stopLoadTagRecord ≠ 1 ]
If [ $$citationMatch = "sample" ]
Go to Field [ ]
#
#The 'sample' variable may have more than one
#key in it. So we need a variable with just this
#records keys in it to conditionally formatt all
#learn window records tagged with it.
Set Variable [ $$tagSample; Value:tagMenus::_Ltag ]
Set Variable [ $$SampleOrTestID; Value:Get (RecordID) ]
If [ $$add = 1 and $$citationMatch = $$addCitationMatch ]
Else If [ $$add = "" ]
End If
Refresh Window
#
#Just in case user was in nonTag ﬁeld on this
#window when user clicked a menu button on
#the other window, exit all ﬁelds.
If [ TEMP::TLSampleSort = "" ]
Set Variable [ $recordNumber; Value:Get (RecordNumber) ]
Select Window [ Name: "Learn"; Current ﬁle ]
Perform Script [ “SortTLRecordsByOrderNumber” ]
Select Window [ Name: "Tag Menus"; Current ﬁle ]
Go to Record/Request/Page [ $recordNumber ]
[ No dialog ]
Set Variable [ $$tagSample; Value:tagMenus::_Ltag ]
Set Field [ TEMP::TLSampleSort; "" ]
End If
Select Window [ Name: "Learn"; Current ﬁle ]
If [ TEMP::TLSampleSort = 1 ]
Set Field [ TEMP::TLSampleSort; "" ]
Perform Script [ “SortTLRecordsByOrderNumber” ]
End If
Go to Field [ ]
Refresh Window
Select Window [ Name: "Tag Menus"; Current ﬁle ]
Refresh Window
End If
End If
January 7, 平成26 16:13:34 Imagination Quality Management.fp7 - loadItemRecordForLearnTagMenuDELETE!!! -1-
