tagMenu: SortTLRecordsByOrderNumber
#
#Perform script for sample and test tags only.
If [ $$citationMatch = "sample" or $$citationMatch = "test"
 or
Left ( Get (LayoutName) ; 4 ) = "test" ]
#
#Make a key for the current record's lock so after
#this sort is complete the system can go back to
#this record.
Set Variable [ $recordKey; Value:testlearn::_Ltestlearn ]
#
#Turn off the loadcitation script to speed up the
#loop portion of the script.
Set Variable [ $$stoploadCitation; Value:1 ]
#
#Check if the user does or does not want sample
#test learn table records sorted by order number.
#If they do (the tlsamplesort is blank) then sort
#by order number.
If [ TEMP::TLSampleSort = "order" and $$citationMatch = "sample" ]
#
#Set the tlsamplesort ﬁeld with a 1. Now if user
#clicks the sort button it will be because they
#now want the records sorted by date.
Set Field [ TEMP::TLSampleSort; 1 ]
#
#To speed up the process, sort to the top the records
#that have ksample numbers. Do not loop thru
#records whose ksample records are blank.
Sort Records [ Speciﬁed Sort Order: testlearn::kcsample; descending ]
[ Restore; No dialog ]
#
#Go the ﬁrst record.
Go to Record/Request/Page
[ First ]
#
#Check the sample key ﬁelds if in sample mode.
If [ $$citationMatch = "sample" ]
Loop
#The ﬁrst step is to blank or clear each record's
#order ﬁeld, so only those records that are part
#of the current sample or test will have order numbers
#and be part of the sort coming right after this
#assignment of sort order numbers.
Set Field [ testlearn::orderTest; "" ]
Exit Loop If [ testlearn::kcsample = "" ]
#
#The order number is the left three digits of a
#sample or test record lock number. ( Remember
#each record in the database has lock number or
#ID number. To open the lock and see any record's
#contents requires a key number that ﬁts the lock.
#So if a lock number is 123, then the key that will
#ﬁt this lock is 123 too. ) Because the sample
#and test key ﬁelds (think of key chains) may
#have several keys, because any one learn record
#may be part of more than one sample or test.
#the system must check each learn record's keys
#one at a time to see if any ﬁt the current sample
#or test's lock. So beginning with number one
#the system checks each key. The left most 3 numbers
#are order numbers so below you will note that
#they system starts the check on the 4th number
#from the left.
Set Variable [ $number; Value:1 ]
Go to Field [ ]
Loop
#
If [ Middle ( GetValue ( testlearn::kcsample ; $number ) ; 4 ; 42 ) & "¶" = $$tagSample & ¶ ]
#
#When and if a key is found that ﬁts the current
#sample or test record's lock, the order number
#( left most 3 digits ) is caputred and placed in
#in the order ﬁeld.
Set Field [ testlearn::orderTest; Left ( GetValue ( testlearn::kcsample ; $number ) ; 3 ) ]
#
#The 'number' variable is made blank to trigger
#the exit from this loop, the order number having
#been assigned.
Set Variable [ $number ]
// Else If [ Middle ( GetValue ( testlearn::kcsample ; $number ) ; 4 ; 42 ) & "¶" ≠ $$tagSample & ¶ ]
// Set Field [ testlearn::orderTest; "" ]
End If
Exit Loop If [ $number = "" ]
#
#Exit loop if the current record is not part
#of the selected sample or test after checking
#all of its keys.
Exit Loop If [ GetValue ( testlearn::kcsample ; $number ) = "" ]
#
#Add 1 to the 'number' varaible after each key
#in the key ﬁeld is checked, to direct the system
#to check the next key.
Set Variable [ $add; Value:$number ]
Set Variable [ $number; Value:$add + 1 ]
End Loop
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
End If
#
#Sort the records by order ﬁeld.
Sort Records [ Speciﬁed Sort Order: testlearn::orderTest; based on value list: “order”
testlearn::timestamp; descending ]
[ Restore; No dialog ]
#
#Return focus to record user was focused on at
#the start of this script.
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
Loop
Exit Loop If [ $recordkey = testlearn::_Ltestlearn ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Turn loadcitation script back on and exit script.
Set Variable [ $$stoploadCitation ]
January 7, 平成26 16:48:34 Imagination Quality Management.fp7 - SortTLRecordsByOrderNumber -1-tagMenu: SortTLRecordsByOrderNumber
Exit Script [ ]
End If
#
#
#
#
#Check if the user does or does not want test
#test learn table records sorted by order number.
#If they do (the tlsampletest is blank) then sort
#by order number.
If [ TEMP::TLTestSort = "order" and $$citationMatch = "test" ]
#
#To speed up the process, sort to the top the records
#that have ksample numbers. Do not loop thru
#records whose ksample records are blank.
Sort Records [ Speciﬁed Sort Order: testlearn::kctest; descending ]
[ Restore; No dialog ]
#
#Go the ﬁrst record.
Go to Record/Request/Page
[ First ]
#
#Check the test key ﬁelds if in sample mode.
If [ $$citationMatch = "test" ]
Loop
#
#The ﬁrst step is to blank or clear each record's
#order ﬁeld, so only those records that are part
#of the current sample or test will have order numbers
#and be part of the sort coming right after this
#assignment of sort order numbers.
Set Field [ testlearn::orderTest; "" ]
Exit Loop If [ testlearn::kctest = "" ]
#
#The order number is the left three digits of a
#sample or test record lock number. ( Remember
#each record in the database has lock number or
#ID number. To open the lock and see any record's
#contents requires a key number that ﬁts the lock.
#So if a lock number is 123, then the key that will
#ﬁt this lock is 123 too. ) Because the sample
#and test key ﬁelds (think of key chains) may
#have several keys, because any one learn record
#may be part of more than one sample or test.
#the system must check each learn record's keys
#one at a time to see if any ﬁt the current sample
#or test's lock. So beginning with number one
#the system checks each key. The left most 3 numbers
#are order numbers so below you will note that
#they system starts the check on the 4th number
#from the left.
Set Variable [ $number; Value:1 ]
Go to Field [ ]
Loop
If [ Middle ( GetValue ( testlearn::kctest ; $number ) ; 4 ; 42 ) & "¶" = $$tagtest & ¶ ]
#
#When and if a key is found that ﬁts the current
#sample or test record's lock, the order number
#( left most 3 digits ) is caputred and placed in
#in the order ﬁeld.
Set Field [ testlearn::orderTest; Left ( GetValue ( testlearn::kctest ; $number ) ; 3 ) ]
#
#The 'number' variable is made blank to trigger
#the exit from this loop, the order number having
#been assigned.
Set Variable [ $number ]
End If
Exit Loop If [ $number = "" ]
#
#Exit loop if the current record is not part
#of the selected sample or test after checking
#all of its keys.
Exit Loop If [ GetValue ( testlearn::kctest ; $number ) = "" ]
#
#Add 1 to the 'number' varaible after each key
#in the key ﬁeld is checked, to direct the system
#to check the next key.
Set Variable [ $add; Value:$number ]
Set Variable [ $number; Value:$add + 1 ]
End Loop
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
End If
#
#Sort the records by order ﬁeld.
Sort Records [ Speciﬁed Sort Order: testlearn::orderTest; based on value list: “order”
testlearn::timestamp; descending ]
[ Restore; No dialog ]
#
#Return focus to record user was focused on at
#the start of this script.
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
Loop
Exit Loop If [ $recordkey = testlearn::_Ltestlearn ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Turn loadcitation script back on and exit script.
Set Variable [ $$stoploadCitation ]
Exit Script [ ]
End If
#
End If
January 7, 平成26 16:48:34 Imagination Quality Management.fp7 - SortTLRecordsByOrderNumber -2-
