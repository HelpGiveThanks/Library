tagMenu: CHUNKaddMainSectionKeysToTagRecordKeychain_addMode
#
#Add any section keys just added to the main record
#that are not in this tag's section group keychain, so that
#this tag will show up in all sections the main record
#shows up in. ( Section tags
# are assigned to groups, not individual tags.
# So if the user wants one tag to be assigned
# to a new section, its group and all tags in
# its group must be assigned to the new section.
# The reason for this is because the display of
# tags by group requires that each group
# have a unique name and that each tag belong
# to a group. )
#
#Determine how many keys there are.
Set Variable [ $numberOfKeys; Value:ValueCount ( $$mainKeychain ) ]
#
#Loop thru each key to see if any do not match
#keys in the tag group's keychain.
Loop
#
#Exit the loop when there are no more keys to check.
Exit Loop If [ $numberOfKeys = 0 ]
#
If [ GetValue ( $$mainKeychain ; $numberOfKeys ) ≠ GetValue ( FilterValues ( ruleTagMenuGroups::ksection & ¶ ; GetValue ( $$mainKeychain ; $numberOfKeys ) & ¶ ) ; 1 ) ]
#
#Next, add the current section key to this
#group's keychain.
Set Variable [ $groupSectionKeychain; Value:ruleTagMenuGroups::ksection ]
Set Field [ ruleTagMenuGroups::ksection; GetValue ( $$mainKeychain ; $numberOfKeys ) & ¶ & $groupSectionKeychain ]
#
End If
#
#Go the next key up from the bottom of the list
#of keys on this section's keychain.
Set Variable [ $numberOfKeys; Value:$numberOfKeys - 1 ]
End Loop
#
January 7, 平成26 16:26:49 Imagination Quality Management.fp7 - CHUNKaddMainSectionKeysToTagRecordKeychain_addMode -1-
