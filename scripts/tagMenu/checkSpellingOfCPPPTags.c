January 20, 2018 18:00:00 Library.fmp12 - checkSpellingOfCPPPTags -1-
tagMenu: checkSpellingOfCPPPTags
#
#
#This script used to do what the disabled comment
#below says. But then I realized it was great
#at backing up spelling of entered tags and
#stopping user from changing spelling of
#locked tags, SO I repuprosed it to do just
#that for copyright (well no longer for those,
#cause user cannot get to an edit layout when
#they are locked), publication, publisher,
#and path tags.
// #Insure accidental running of spelling script
// #will not erase path name. FYI: In normal
// #operation this will not happen, but when
// #coding it is possible to stop a script and then
// #trigger the replace spelling script, which if
// #this field is blank will replace the path with a
// #blank = delete the path.
#
#IMPORTANT!!! Do not lock out user's ability
#to change path tags. These are unique to
#each user's computer, and so to enable
#better sharing, the path tags need to
#remain editable.
If [ tagCreatorLock::orderOrLock ≠ "" and $$citationMatch ≠ "path" ]
Set Field [ tagMenus::tag; tagMenus::tagSpelling ]
Else If [ tagCreatorLock::orderOrLock = "" or $$citationMatch = "path" ]
Set Field [ tagMenus::tagSpelling; tagMenus::tag ]
End If
