testScreens: testReport: reportTagInfo
#basic administration tasks
Set Error Capture [ On ]
Allow User Abort [ Off ]
#
If [ Left ( Get (LayoutName) ; 6 ) = "report" ]
Go to Layout [ “reportTagInfo” (testlearnReportTags) ]
Else If [ Left ( Get (LayoutName) ; 6 ) ≠ "report" ]
Go to Layout [ “testInfo” (testlearnReportTags) ]
End If
#Turn off the loadtagrecord script to speed up the
#loop portion of the script.
Set Variable [ $$stoploadtestinfo; Value:1 ]
Enter Find Mode [ ]
#
#now ﬁnd and show all canned inspection items associated with this generic canned location
Set Field [ testlearnReportTags::kcsection; TEMP::ksection ]
Set Field [ testlearnReportTags::kctest; "###" & $$item ]
Perform Find [ ]
#
#Clear sample and test tags.
Set Variable [ $$tagSample ]
Set Variable [ $$tagtest ]
Set Variable [ $$tagRecordID ]
Set Variable [ $$tagEdit ]
#
#
#If sort by order number is on then sort by
#order number.
#Go the ﬁrst record.
Go to Record/Request/Page
[ First ]
#
Loop
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
#The ﬁrst step is to blank or clear each record's
#order ﬁeld, so only those records that are part
#of the current sample or test will have order numbers
#and be part of the sort coming right after this
#assignment of sort order numbers.
Set Field [ testlearnReportTags::orderTest; "" ]
#
#When and if a key is found that ﬁts the current
#sample or test record's lock, the order number
#( left most 3 digits ) is caputred and placed in
#in the order ﬁeld.
Set Field [ testlearnReportTags::orderTest; Left ( GetValue ( testlearnReportTags::kctest ; $number ) ; 3 ) ]
#
#The 'number' variable is made blank to trigger
#the exit from this loop, the order number having
#been assigned.
Set Variable [ $number ]
Exit Loop If [ $number = "" ]
#
#Exit loop if the current record is not part
#of the selected sample or test after checking
#all of its keys.
Exit Loop If [ GetValue ( testlearnReportTags::kctest ; $number ) = "" ]
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
#
#Sort the records by order ﬁeld.
Sort Records [ Speciﬁed Sort Order: testlearnReportTags::orderTest; based on value list: “order”
testlearnReportTags::timestamp; descending ]
[ Restore; No dialog ]
#
#Return focus to record user was focused on at
#the start of this script.
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
#
#Turn loadcitation script back on and exit script.
Set Variable [ $$stoploadtestinfo ]
Perform Script [ “loadtestinfo” ]
January 7, 平成26 14:41:42 Imagination Quality Management.fp7 - reportTagInfo -1-
