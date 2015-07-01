tagMenu: CHUNKaddMainRecordSectionKeysToCiteOrRefSectionKeychain
#
#
Select Window [ Name: "Learn"; Current file ]
If [ Get (LastError) = 0 ]
Set Variable [ $keychain; Value:testlearn::kcsection ]
#
#
#BEGIN — NO LONGER USED I think. Testing required.
// #If learn record that tag was added
// #to belongs to more than one section, then
// #add these other sections to the learn or reference
// #keychain so when this learn record is viewed in
// #those sections, the reference or learn record
// #just added to it will show up as well.
// #NOTE: Once a learn record is tagged with reference
// #records -- other learn and reference records --
// #it is prevented in add mode from acquiring new keys
// #which would need to be passed along to these added
// #records, and then to all of their references, and so on.
If [ testlearn::kcitation ≠ "" and $$citationMatch = "ref" ]
Show Custom Dialog [ Message: "References can be added after the citation is removed. (Cite the source of an unchanged copy, clip, quote, etc. from one source. Reference the sources of your rewording/remixing of one or more texts, movies, etc.)"; Buttons: “OK” ]
Select Window [ Name: "Tag Menus"; Current file ]
Halt Script
Else If [ testlearn::kcreference ≠ "" and $$citationMatch = "cite" ]
If [ ValueCount ( testlearn::kcreference ) = 1 ]
Show Custom Dialog [ Message: "A citiation can be added after the referene is removed. (Cite the source of an unchanged copy, clip, quote, etc. from one source. Reference the sources of your rewording/remixing of one or more texts, movies, etc.)"; Buttons: “OK” ]
Else
Show Custom Dialog [ Message: "A citiation can be added after referenes are removed. (Cite the source of an unchanged copy, clip, quote, etc. from one source. Reference the sources of your rewording/remixing of one or more texts, movies, etc.)"; Buttons: “OK” ]
End If
Select Window [ Name: "Tag Menus"; Current file ]
Halt Script
End If
#END — NO LONGER USED I think. Testing required.
#
#
Else If [ Get (LastError) ≠ 0 ]
Select Window [ Name: "References"; Current file ]
Set Variable [ $keychain; Value:reference::kcsection ]
End If
#
#Determine how many keys there are.
Set Variable [ $numberOfKeys; Value:ValueCount ( $keychain ) ]
#
#Loop thru each key to see if any do not match
#keys in the main record's keychain.
Select Window [ Name: "Tag Menus"; Current file ]
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
#Stop script if user trying to add reference or learn record
#that has references or citations added to it.
#Records being added to have to share their section
#keys with all records being added to them. But
#when a record is addd that is missing some of its
#is added AND that record has records added to it
#as a citation or reference life gets really complicated.
#So to simplify things for now, tag adding cannot happen
#once a record aquires references and tags. A record
#can be added as a reference or a citation as long as
#it is has all the tags of the record it is being added to.
If [ testlearn::kcitation ≠ "" or testlearn::kcreference ≠ "" or reference::kcitation ≠ "" ]
Show Custom Dialog [ Message: "This record you wish to add can be added if you first remove the citation or references that are linked to it. Once added, these removed records can be added back."; Buttons: “OK” ]
Halt Script
End If
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
#Stop script if user trying to add reference or learn record
#that has references or citations added to it.
#Records being added to have to share their section
#keys with all records being added to them. But
#when a record is addd that is missing some of its
#is added AND that record has records added to it
#as a citation or reference life gets really complicated.
#So to simplify things for now, tag adding cannot happen
#once a record aquires references and tags. A record
#can be added as a reference or a citation as long as
#it is has all the tags of the record it is being added to.
If [ testlearn::kcitation ≠ "" or testlearn::kcreference ≠ "" or reference::kcitation ≠ "" ]
Show Custom Dialog [ Message: "This record you wish to add can be added if you first remove the citation or references that are linked to it. Once added, these removed records can be added back."; Buttons: “OK” ]
Halt Script
End If
#
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
July 1, 平成27 12:45:05 Library.fp7 - CHUNKaddMainRecordSectionKeysToCiteOrRefSectionKeychain -1-
