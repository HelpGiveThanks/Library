tagMenu: addTagSectionKeysToMainRecordKeychain
#
#Add all tag's section keys to reference or learn record,
#so that wherever this tag is with this learn or reference
#record's picture, the record the picture came from is
#also available. This is especially important if the user
#decides to include only one section. The picture-
#containing record needs to be part of that section!
#BUT, the tag does not need to be in every section
#this picture-containing record is in, unless this record
#is tagged with the tag it is adding the picture to.
#NOTE: add section keys only to keyword and node tags.
If [ $$citationMatch = "node" or $$citationMatch = "key" ]
#
#Discover ﬁrst if the section keys in the tag's
#keychain are also in the Main record's keychain.
Select Window [ Name: "Tag Menus"; Current ﬁle ]
Set Variable [ $keychain; Value:ruleTagMenuGroups::ksection ]
#
#Capture the tag's key to determin later if it is in any
#of this learn or reference record's key ﬁelds.
Set Variable [ $tagKey; Value:tagMenus::_Ltag ]
#
#Determine how many keys there are in the tag's
#keychain.
Set Variable [ $numberOfKeys; Value:ValueCount ( $keychain ) ]
#
#Loop thru each key to see if any do not match
#keys in the main record's keychain.
Select Window [ Name: "References"; Current ﬁle ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current ﬁle ]
End If
Loop
#
#Exit the loop when there are no more keys to check.
Exit Loop If [ $numberOfKeys = 0 ]
#
#If main record being tagged does not have
#one or more of the tag's keys in its keychain then
#add the missing keys.
If [ Get ( LayoutTableName ) = "testlearn" and
GetValue ( $keychain ; $numberOfKeys ) ≠
GetValue ( FilterValues ( testlearn::kcsection & ¶ ; GetValue ( $keychain ; $numberOfKeys ) & ¶ ) ; 1 ) ]
#
#Next, add the current section key to this
#group's keychain.
Set Variable [ $groupSectionKeychain; Value:testlearn::kcsection ]
Set Field [ testlearn::kcsection; GetValue ( $keychain ; $numberOfKeys ) & ¶ & $groupSectionKeychain ]
#
Else If [ Get ( LayoutTableName ) = "reference" and
GetValue ( $keychain ; $numberOfKeys ) ≠
GetValue ( FilterValues ( reference::kcsection & ¶ ; GetValue ( $keychain ; $numberOfKeys ) & ¶ ) ; 1 ) ]
#
#Next, add the current section key to this
#group's keychain.
Set Variable [ $groupSectionKeychain; Value:reference::kcsection ]
Set Field [ reference::kcsection; GetValue ( $keychain ; $numberOfKeys ) & ¶ & $groupSectionKeychain ]
#
End If
#
#Go the next key up from the bottom of the list
#of keys on this section's keychain.
Set Variable [ $numberOfKeys; Value:$numberOfKeys - 1 ]
End Loop
#
End If
January 7, 平成26 16:34:22 Imagination Quality Management.fp7 - addTagSectionKeysToMainRecordKeychain -1-
