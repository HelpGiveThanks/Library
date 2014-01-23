tagMenu: setOrderForSampleOrTest
#
#Get order number user has selected then exit
#the order ﬁeld.
Go to Field [ ]
Set Variable [ $order; Value:testlearn::orderTest ]
#
#If record is not part of a sample or test exit script.
If [ $$citationMatch = "sample" and testlearn::kcsample = "" ]
Set Field [ testlearn::orderTest; "" ]
Show Custom Dialog [ Message: "You can apply an order number to this record when you make it part of a sample by clicking any square button in Tag Menus window next to a sample tag."; Buttons: “OK” ]
Exit Script [ ]
Else If [ $$citationMatch = "test" and testlearn::kctest = "" ]
Set Field [ testlearn::orderTest; "" ]
Show Custom Dialog [ Message: "You can apply an order number to this record when you make it part of a test by clicking any square button in Tag Menus window next to a test tag."; Buttons: “OK” ]
Exit Script [ ]
End If
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
If [ $$citationMatch = "sample" ]
Loop
If [ Middle ( GetValue ( testlearn::kcsample ; $number ) ; 4 ; 42 ) & "¶" = $$tagSample & ¶ ]
Set Variable [ $replacementValue; Value:Replace ( GetValue ( testlearn::kcsample ; $number ) ; 1 ; 3 ; $order ) ]
#
#When and if a key is found that ﬁts the current
#sample or test record's lock, the order number
#the user has selected overwrites the left most
#3 digits which by default are 999.
Set Field [ testlearn::kcsample; Substitute ( $$sample ; GetValue ( testlearn::kcsample ; $number ) & "¶" ; $replacementValue & ¶) ]
#
#The 'sample' variable is resset to reﬂect this change
Set Variable [ $$sample; Value:testlearn::kcsample ]
Set Variable [ $$citationItem ]
#
#The 'number' variable is made blank to trigger
#the exit from this loop, the key having been found.
Set Variable [ $number ]
End If
Exit Loop If [ $number = "" ]
#
#Exit the script if the current record is not part
#of the selected sample or test after checking
#all of its keys.
If [ GetValue ( testlearn::kcsample ; $number ) = "" ]
Set Field [ testlearn::orderTest; "" ]
Show Custom Dialog [ Message: "You can apply an order number to this record when you make it part of the selected sample by clicking the square button in Tag Menus window next to it."; Buttons: “OK” ]
Exit Script [ ]
End If
#
#Add 1 to the 'number' varaible after each key
#in the key ﬁeld is checked, to direct the system
#to check the next key.
Set Variable [ $add; Value:$number ]
Set Variable [ $number; Value:$add + 1 ]
End Loop
#
Else If [ $$citationMatch = "test" ]
Loop
If [ Middle ( GetValue ( testlearn::kctest ; $number ) ; 4 ; 42 ) & "¶" = $$tagtest & ¶ ]
Set Variable [ $replacementValue; Value:Replace ( GetValue ( testlearn::kctest ; $number ) ; 1 ; 3 ; $order ) ]
#
#When and if a key is found that ﬁts the current
#sample or test record's lock, the order number
#the user has selected overwrites the left most
#3 digits which by default are 999.
Set Field [ testlearn::kctest; Substitute ( $$test ; GetValue ( testlearn::kctest ; $number ) & "¶" ; $replacementValue & ¶) ]
#
#The 'test' variable is resset to reﬂect this change
Set Variable [ $$test; Value:testlearn::kctest ]
Set Variable [ $$citationItem ]
#
#The 'number' variable is made blank to trigger
#the exit from this loop, the key having been found.
Set Variable [ $number ]
End If
Exit Loop If [ $number = "" ]
#
#Exit the script if the current record is not part
#of the selected sample or test after checking
#all of its keys.
If [ GetValue ( testlearn::kctest ; $number ) = "" ]
Set Field [ testlearn::orderTest; "" ]
Show Custom Dialog [ Message: "You can apply an order number to this record when you make it part of the selected test by clicking the square button in Tag Menus window next to it."; Buttons: “OK” ]
Exit Script [ ]
End If
#
#Add 1 to the 'number' varaible after each key
#in the key ﬁeld is checked, to direct the system
#to check the next key.
Set Variable [ $add; Value:$number ]
Set Variable [ $number; Value:$add + 1 ]
End Loop
End If
Sort Records [ ]
[ No dialog ]
January 7, 平成26 16:08:22 Imagination Quality Management.fp7 - setOrderForSampleOrTest -1-
