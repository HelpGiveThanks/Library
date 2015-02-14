tagMenu: CHUNKaddMainSectionKeysToTagRecordKeychain
#
#If reference or learn record that tag was added
#to belongs to more than one section, then
#add these other sections to the tag's group
#keychain so when this tag record is viewed in
#those sections, the reference or learn record
#just added to it will show up as well.
#NOTE: Add only section keys to keyword and node tags.
If [ $$citationMatch = "node" or $$citationMatch = "key" ]
Select Window [ Name: "References"; Current file ]
Set Variable [ $keychain; Value:reference::kcsection ]
Select Window [ Name: "Learn"; Current file ]
#
#If the user was not looking at Refernce records
#then the keychain variable will be blank and need
#to be filled in. But if they were then filling it in
#as if Learn records where showing would blank
#the just filled in keychain variable.
If [ $keychain = "" ]
Set Variable [ $keychain; Value:testlearn::kcsection ]
End If
#
#Determine how many keys there are.
Set Variable [ $numberOfKeys; Value:ValueCount ( $keychain ) ]
#
#Loop thru each key to see if any do not match
#keys in the tag group's keychain.
Select Window [ Name: "Tag Menus"; Current file ]
Loop
#
#Exit the loop when there are no more keys to check.
Exit Loop If [ $numberOfKeys = 0 ]
#
If [ GetValue ( $keychain ; $numberOfKeys ) ≠ GetValue ( FilterValues ( ruleTagMenuGroups::ksection & ¶ ; GetValue ( $keychain ; $numberOfKeys ) & ¶ ) ; 1 ) ]
#
#Next, add the current section key to this
#group's keychain.
Set Variable [ $groupSectionKeychain; Value:ruleTagMenuGroups::ksection ]
Set Field [ ruleTagMenuGroups::ksection; GetValue ( $keychain ; $numberOfKeys ) & ¶ & $groupSectionKeychain ]
#
End If
#
#Go the next key up from the bottom of the list
#of keys on this section's keychain.
Set Variable [ $numberOfKeys; Value:$numberOfKeys - 1 ]
End Loop
End If
#
January 7, 平成26 16:27:21 Imagination Quality Management.fp7 - CHUNKaddMainSectionKeysToTagRecordKeychain -1-
