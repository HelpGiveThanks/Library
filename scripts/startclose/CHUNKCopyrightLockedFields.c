July 21, 2018 13:31:59 Library.fmp12 - CHUNK_CopyrightLockedFields -1-
startclose: CHUNK_CopyrightLockedFields
#
#
#Admin tasks.
Set Error Capture [ On ]
Allow User Abort [ Off ]
#
#
#Refresh copyright groups by deleting them
#and then recreating them.
Go to Layout [ “tableTagGroup” (testSubsectionGroup) ]
Perform Find [ Specified Find Requests: Find Records; Criteria: testSubsectionGroup::orderOrLibraryType: “"lock"” ]
[ Restore ]
If [ Get ( LastError ) = 0 ]
Delete All Records
[ No dialog ]
End If
#
#0 Share - all copyrights given up by creator
New Record/Request
Set Field [ testSubsectionGroup::orderOrLibraryType; "lock" ]
Set Field [ testSubsectionGroup::match; "copyright" ]
Set Field [ testSubsectionGroup::kRecordCreatorNode; "defaultCopyrightGroup" ]
#1308
Set Field [ testSubsectionGroup::_Number; 1308 ]
Set Field [ testSubsectionGroup::_Lgroup; 31620121911511308 ]
Set Variable [ $name; Value:"0 Share - all copyrights given up by creator" ]
Set Field [ testSubsectionGroup::name; $name ]
Set Field [ testSubsectionGroup::nameSpellingEXCEPTForTestItemGroup; $name ]
#
#1a Share - public domain possibly everywhere
New Record/Request
Set Field [ testSubsectionGroup::orderOrLibraryType; "lock" ]
Set Field [ testSubsectionGroup::match; "copyright" ]
Set Field [ testSubsectionGroup::kRecordCreatorNode; "defaultCopyrightGroup" ]
#1306
Set Field [ testSubsectionGroup::_Number; 1308 ]
Set Field [ testSubsectionGroup::_Lgroup; 31620121853131306 ]
Set Variable [ $name; Value:"1a Share - public domain possibly everywhere" ]
Set Field [ testSubsectionGroup::name; $name ]
Set Field [ testSubsectionGroup::nameSpellingEXCEPTForTestItemGroup; $name ]
#
#1b Share - public domain in some places, not all
New Record/Request
Set Field [ testSubsectionGroup::orderOrLibraryType; "lock" ]
Set Field [ testSubsectionGroup::match; "copyright" ]
Set Field [ testSubsectionGroup::kRecordCreatorNode; "defaultCopyrightGroup" ]
#554
Set Field [ testSubsectionGroup::_Number; 554 ]
Set Field [ testSubsectionGroup::_Lgroup; 8172011134941554 ]
Set Variable [ $name; Value:"1b Share - public domain in some places, not all" ]
Set Field [ testSubsectionGroup::name; $name ]
Set Field [ testSubsectionGroup::nameSpellingEXCEPTForTestItemGroup; $name ]
#
#2 Share and give credit CC BY
New Record/Request
Set Field [ testSubsectionGroup::orderOrLibraryType; "lock" ]
Set Field [ testSubsectionGroup::match; "copyright" ]
Set Field [ testSubsectionGroup::kRecordCreatorNode; "defaultCopyrightGroup" ]
#1302
Set Field [ testSubsectionGroup::_Number; 1302 ]
Set Field [ testSubsectionGroup::_Lgroup; 31620121746441302 ]
Set Variable [ $name; Value:"2 Share and give credit" ]
Set Field [ testSubsectionGroup::name; $name ]
Set Field [ testSubsectionGroup::nameSpellingEXCEPTForTestItemGroup; $name ]
#
#3 Share, give credit, and use the same copyright license CC BY-SA
New Record/Request
Set Field [ testSubsectionGroup::orderOrLibraryType; "lock" ]
Set Field [ testSubsectionGroup::match; "copyright" ]
Set Field [ testSubsectionGroup::kRecordCreatorNode; "defaultCopyrightGroup" ]
#1305
Set Field [ testSubsectionGroup::_Number; 1305 ]
Set Field [ testSubsectionGroup::_Lgroup; 31620121841541305 ]
Set Variable [ $name; Value:"3 Share, give credit, and use the same copyright license" ]
Set Field [ testSubsectionGroup::name; $name ]
Set Field [ testSubsectionGroup::nameSpellingEXCEPTForTestItemGroup; $name ]
#
#4 Share, give credit, and don’t change CC BY-ND
New Record/Request
Set Field [ testSubsectionGroup::orderOrLibraryType; "lock" ]
Set Field [ testSubsectionGroup::match; "copyright" ]
Set Field [ testSubsectionGroup::kRecordCreatorNode; "defaultCopyrightGroup" ]
#1307
Set Field [ testSubsectionGroup::_Number; 1307 ]
Set Field [ testSubsectionGroup::_Lgroup; 31620121902441307 ]
Set Variable [ $name; Value:"4 Share, give credit, and don’t change" ]
Set Field [ testSubsectionGroup::name; $name ]
Set Field [ testSubsectionGroup::nameSpellingEXCEPTForTestItemGroup; $name ]
#
#5 Share, give credit, and don’t sell CC BY-NC
New Record/Request
Set Field [ testSubsectionGroup::orderOrLibraryType; "lock" ]
Set Field [ testSubsectionGroup::match; "copyright" ]
Set Field [ testSubsectionGroup::kRecordCreatorNode; "defaultCopyrightGroup" ]
#1304
Set Field [ testSubsectionGroup::_Number; 1304 ]
Set Field [ testSubsectionGroup::_Lgroup; 31620121837161304 ]
Set Variable [ $name; Value:"5 Share, give credit, and don’t sell" ]
Set Field [ testSubsectionGroup::name; $name ]
Set Field [ testSubsectionGroup::nameSpellingEXCEPTForTestItemGroup; $name ]
#
#6 Share, give credit, don’t sell, and use the same copyright license CC BY-NC-SA
New Record/Request
Set Field [ testSubsectionGroup::orderOrLibraryType; "lock" ]
Set Field [ testSubsectionGroup::match; "copyright" ]
Set Field [ testSubsectionGroup::kRecordCreatorNode; "defaultCopyrightGroup" ]
#553
Set Field [ testSubsectionGroup::_Number; 553 ]
Set Field [ testSubsectionGroup::_Lgroup; 8162011231825553 ]
Set Variable [ $name; Value:"6 Share, give credit, don’t sell, and use the same copyright license" ]
Set Field [ testSubsectionGroup::name; $name ]
Set Field [ testSubsectionGroup::nameSpellingEXCEPTForTestItemGroup; $name ]
#
#7 Share, give credit, don’t sell, don't change CC BY-NC-ND
New Record/Request
Set Field [ testSubsectionGroup::orderOrLibraryType; "lock" ]
Set Field [ testSubsectionGroup::match; "copyright" ]
Set Field [ testSubsectionGroup::kRecordCreatorNode; "defaultCopyrightGroup" ]
#1303
Set Field [ testSubsectionGroup::_Number; 1303 ]
Set Field [ testSubsectionGroup::_Lgroup; 31620121824141303 ]
Set Variable [ $name; Value:"7 Share, give credit, don’t sell, don't change" ]
Set Field [ testSubsectionGroup::name; $name ]
Set Field [ testSubsectionGroup::nameSpellingEXCEPTForTestItemGroup; $name ]
#
#8 Don’t share - personal use only
New Record/Request
Set Field [ testSubsectionGroup::orderOrLibraryType; "lock" ]
Set Field [ testSubsectionGroup::match; "copyright" ]
Set Field [ testSubsectionGroup::kRecordCreatorNode; "defaultCopyrightGroup" ]
#540
Set Field [ testSubsectionGroup::_Number; 540 ]
Set Field [ testSubsectionGroup::_Lgroup; 8102011220941540 ]
Set Variable [ $name; Value:"8 Don’t share - personal use only" ]
Set Field [ testSubsectionGroup::name; $name ]
Set Field [ testSubsectionGroup::nameSpellingEXCEPTForTestItemGroup; $name ]
#
#Trademark, Service Mark, Logo, Etc.
New Record/Request
Set Field [ testSubsectionGroup::orderOrLibraryType; "lock" ]
Set Field [ testSubsectionGroup::match; "copyright" ]
Set Field [ testSubsectionGroup::kRecordCreatorNode; "defaultCopyrightGroup" ]
#1809
Set Field [ testSubsectionGroup::_Number; 1809 ]
Set Field [ testSubsectionGroup::_Lgroup; 92020171119521809 ]
Set Variable [ $name; Value:"Trademark, Service Mark, Logo, Etc." ]
Set Field [ testSubsectionGroup::name; $name ]
Set Field [ testSubsectionGroup::nameSpellingEXCEPTForTestItemGroup; $name ]
#
#
#
#
#
#
#
#Refresh locked tag records (filelocation,
#inventory location headers, and copyright
#records) by deleting them and then
#recreating them.
Go to Layout [ “tableTag” (tagTable) ]
Perform Find [ Specified Find Requests: Find Records; Criteria: tagTable::orderOrLock: “"lock"” ]
[ Restore ]
Delete All Records
[ No dialog ]
#
#
#
#
#
#
#Refresh filelocation records for Reference
#edit layouts' location checkboxes.
New Record/Request
Set Field [ tagTable::tag; "x" ]
Set Field [ tagTable::_Number; 313 ]
Set Field [ tagTable::tagSpelling; "x" ]
Set Field [ tagTable::orderOrLock; "lock" ]
Set Field [ tagTable::match; "fileLocation" ]
Set Field [ tagTable::_Ltag; "8162011225532313" ]
Set Field [ tagTable::kRecordCreatorNode; "defaultFilePathCheckBox" ]
#
New Record/Request
Set Field [ tagTable::tag; "main" ]
Set Field [ tagTable::_Number; 314 ]
Set Field [ tagTable::tagSpelling; "main" ]
Set Field [ tagTable::orderOrLock; "lock" ]
Set Field [ tagTable::match; "fileLocation" ]
Set Field [ tagTable::_Ltag; "8162011225558314" ]
Set Field [ tagTable::kRecordCreatorNode; "defaultFilePathCheckBox" ]
#
New Record/Request
Set Field [ tagTable::tag; "other" ]
Set Field [ tagTable::_Number; 315 ]
Set Field [ tagTable::tagSpelling; "other" ]
Set Field [ tagTable::orderOrLock; "lock" ]
Set Field [ tagTable::match; "fileLocation" ]
Set Field [ tagTable::_Ltag; "8162011225605315" ]
Set Field [ tagTable::kRecordCreatorNode; "defaultFilePathCheckBox" ]
#
#
#
#
#
#
#
#Refresh inventory library's 3 location groups.
New Record/Request
Set Field [ tagTable::tag; "primary location" ]
Set Field [ tagTable::_Number; 3386 ]
Set Field [ tagTable::tagSpelling; "primary location" ]
Set Field [ tagTable::orderOrLock; "lock" ]
Set Field [ tagTable::match; "location" ]
Set Field [ tagTable::_Ltag; "31120182009273386" ]
Set Field [ tagTable::kRecordCreatorNode; "defaultLocation" ]
#
New Record/Request
Set Field [ tagTable::tag; "secondary location" ]
Set Field [ tagTable::_Number; 3387 ]
Set Field [ tagTable::tagSpelling; "secondary location" ]
Set Field [ tagTable::orderOrLock; "lock" ]
Set Field [ tagTable::match; "location" ]
Set Field [ tagTable::_Ltag; "31120182009473387" ]
Set Field [ tagTable::kRecordCreatorNode; "defaultLocation" ]
#
New Record/Request
Set Field [ tagTable::tag; "tertiary location" ]
Set Field [ tagTable::_Number; 3388 ]
Set Field [ tagTable::tagSpelling; "tertiary location" ]
Set Field [ tagTable::orderOrLock; "lock" ]
Set Field [ tagTable::match; "location" ]
Set Field [ tagTable::_Ltag; 31120182009593388 ]
Set Field [ tagTable::kRecordCreatorNode; "defaultLocation" ]
#
#
#
#
#
#
#
#
#Refresh copyright records.
#
#0 Share - all copyrights given up by creator
New Record/Request
Set Field [ tagTable::kGroupOrTest; 31620121911511308 ]
Set Field [ tagTable::match; "copyright" ]
Set Field [ tagTable::orderOrLock; "lock" ]
Set Field [ tagTable::kRecordCreatorNode; "defaultCopyright" ]
#1235
Set Field [ tagTable::_Number; 1235 ]
Set Field [ tagTable::_Ltag; 31620121911511235 ]
Set Variable [ $tag; Value:"CC0 1.0 — Creative Commons Universal Public Domain Dedication " & Quote ( "No Rights Reserved" ) ]
Set Field [ tagTable::tag; $tag ]
Set Field [ tagTable::tagSpelling; $tag ]
Set Field [ tagTable::notesOrCopyright; ¶ &
TextSize ( TextColor ( TextFont ( "[NOTE: Click the 'web' button above to view the most current and complete source of the text
below, copied on September 22, 2017 from creativecommons.org/publicdomain/zero/1.0/ for your convenience.]" & ¶ ; "Arial" ) ;
RGB ( 51 ; 51 ; 51 ) ) ; 16 )
& ¶ &
TextStyleAdd ( "CC0 1.0 Universal (CC0 1.0) Universal Public Domain Dedication" ; Bold )
& ¶ & ¶ &
"This is a human-readable summary of the Legal Code (read the full text). Disclaimer"
& ¶ & ¶ &
TextStyleAdd ( "No Copyright" ; Bold )
& ¶ &
"The person who associated a work with this deed has dedicated the work to the public domain by waiving all of his or her rights to
the work worldwide under copyright law, including all related and neighboring rights, to the extent allowed by law."
& ¶ & ¶ &
"You can copy, modify, distribute and perform the work, even for commercial purposes, all without asking permission. See Other
Information below. "
& ¶ & ¶ &
TextStyleAdd ( "Other Information" ; Bold )
& ¶ &
" • In no way are the patent or trademark rights of any person affected by CC0, nor are the rights that other persons may have in
the work or in how the work is used, such as publicity or privacy rights."
& ¶ &
" • Unless expressly stated otherwise, the person who associated a work with this deed makes no warranties about the work,
and disclaims liability for all uses of the work, to the fullest extent permitted by applicable law."
& ¶ &
" • When using or citing the work, you should not imply endorsement by the author or the affirmer." ]
Set Field [ tagTable::Ktitle1; 3162012191328147 ]
Set Field [ tagTable::Kpicture1; 92020172213321496 ]
#
#
#
#0 Share - all copyrights given up by creator
New Record/Request
Set Field [ tagTable::kGroupOrTest; 31620121911511308 ]
Set Field [ tagTable::match; "copyright" ]
Set Field [ tagTable::orderOrLock; "lock" ]
Set Field [ tagTable::kRecordCreatorNode; "defaultCopyright" ]
#4557
Set Field [ tagTable::_Number; 4557 ]
Set Field [ tagTable::_Ltag; 92120171055254557 ]
Set Variable [ $tag; Value:"PD by Creator — I, the copyright holder of this work, release this work into the public domain. This applies
worldwide.
In some countries this may not be legally possible; if so:
I grant anyone the right to use this work for any purpose, without any conditions, unless such conditions are required by law." ]
Set Field [ tagTable::tag; $tag ]
Set Field [ tagTable::tagSpelling; $tag ]
Set Field [ tagTable::notesOrCopyright; ¶ &
TextSize ( TextColor ( TextFont ( "[NOTE: Click the 'web' button above to view the most current and complete source of the text
excerpts below, copied on September 22, 2017 from https://commons.wikimedia.org/wiki/Template:PD-self for your convenience.]"
& ¶ ; "Arial" ) ; RGB ( 51 ; 51 ; 51 ) ) ; 16 )
& ¶ &
TextStyleAdd ( "Template:PD-self" ; Bold )
& ¶ & ¶ &
"I, the copyright holder of this work, release this work into the public domain. This applies worldwide.
" & ¶ & ¶ &
"In some countries this may not be legally possible; if so:
" & ¶ & ¶ &
"I grant anyone the right to use this work for any purpose, without any conditions, unless such conditions are required by law." ]
Set Field [ tagTable::Ktitle1; 92120171058331505 ]
Set Field [ tagTable::Kpicture1; 92120171043101504 ]
#
#
#
#1a Share - public domain possibly everywhere
New Record/Request
Set Field [ tagTable::kGroupOrTest; 31620121853131306 ]
Set Field [ tagTable::match; "copyright" ]
Set Field [ tagTable::orderOrLock; "lock" ]
Set Field [ tagTable::kRecordCreatorNode; "defaultCopyright" ]
#1228
Set Field [ tagTable::_Number; 1228 ]
Set Field [ tagTable::_Ltag; 31620121743201228 ]
Set Variable [ $tag; Value:"CC PD — Creative Commons Public Domain Mark" ]
Set Field [ tagTable::tag; $tag ]
Set Field [ tagTable::tagSpelling; $tag ]
Set Field [ tagTable::notesOrCopyright; ¶ &
TextSize ( TextColor ( TextFont ( "[NOTE: Click the 'web' button above to view the most current and complete source of the text
below, copied on September 22, 2017 from creativecommons.org/share-your-work/public-domain/pdm/ for your convenience.]" &
¶ ; "Arial" ) ; RGB ( 51 ; 51 ; 51 ) ) ; 16 )
& ¶ &
TextStyleAdd ( "Public Domain Mark" ; Bold )
& ¶ & ¶ &
Quote ( "No Known Copyright" )
& ¶ & ¶ &
"Our Public Domain Mark enables works that are no longer restricted by copyright to be marked as such in a standard and simple
way, making them easily discoverable and available to others. Many cultural heritage institutions including museums, libraries and
other curators are knowledgeable about the copyright status of paintings, books and manuscripts, photographs and other works in
their collections, many of which are old and no longer under copyright. The Public Domain Mark operates as a tag or a label,
allowing institutions like those as well as others with such knowledge to communicate that a work is no longer restricted by
copyright and can be freely used by others. The mark can also be an important source of information, allowing others to verify a
work’s copyright status and learn more about the work."
& ¶ & ¶ &
TextStyleAdd ( "Recommended Uses of the Public Domain Mark" ; Bold )
& ¶ &
"The Public Domain Mark is recommended for works that are free of known copyright around the world. These will typically be very
old works. It is " & TextStyleAdd ( "not" ; Bold ) & " recommended for use with works that are in the public domain in some
jurisdictions if they also known to be restricted by copyright in others."
& ¶ & ¶ &
"A work may have limited or " & Quote ( "hybrid" ) & " public domain status for several reasons. Some jurisdictions have unusually
long copyright terms, which may mean that a work free from copyright restrictions most everywhere in the world could still be
protected by the copyright laws of that particular country. Sometimes a work is no longer restricted by copyright in a jurisdiction
because the author or owner failed to comply with local formalities such as renewal, where those formalities apply. It could also be
the case for works that are deemed not protected by copyright by operation of law in a particular jurisdiction, but that are afforded
protection under the copyright laws of other jurisdictions."
 & ¶ & ¶ &
"CC does not recommend the Public Domain Mark for works with limited, hybrid public domain status at this time, though we will
be exploring means for doing so in 2014."
& ¶ & ¶ &
TextStyleAdd ( "• Learn more about the Public Domain Mark" ; Bold )
& ¶ & ¶ &
TextStyleAdd ( "• Use the Public Domain Mark to label public domain works" ; Bold ) ]
Set Field [ tagTable::Ktitle1; 1122012003249115 ]
Set Field [ tagTable::Kpicture1; 92020172201021493 ]
#
#
#
#1a Share - public domain possibly everywhere
New Record/Request
Set Field [ tagTable::kGroupOrTest; 31620121853131306 ]
Set Field [ tagTable::match; "copyright" ]
Set Field [ tagTable::orderOrLock; "lock" ]
Set Field [ tagTable::kRecordCreatorNode; "defaultCopyright" ]
#9228
Set Field [ tagTable::_Number; 9228 ]
Set Field [ tagTable::_Ltag; 91620171343209228 ]
Set Variable [ $tag; Value:"Ineligible for copyright" ]
Set Field [ tagTable::tag; $tag ]
Set Field [ tagTable::tagSpelling; $tag ]
Set Field [ tagTable::notesOrCopyright; ¶ &
TextSize ( TextColor ( TextFont ( "[NOTE: Click the 'web' button above to view the most current and complete source of the text
excerpts below, copied on September 22, 2017 from commons.wikimedia.org/wiki/Template:PD-ineligible for your convenience.]"
& ¶ ; "Arial" ) ; RGB ( 51 ; 51 ; 51 ) ) ; 16 )
& ¶ &
TextStyleAdd ( "Template:PD-ineligible" ; Bold )
& ¶ & ¶ &
"This file is ineligible for copyright and is therefore in the public domain because it consists entirely of information that is common
property and contains no original authorship.
" & ¶ & ¶ &
"Use this template to mark a file which you have identified as being ineligible for copyright protection by virtue of it 1.) consisting
only of information that is itself in the public domain and 2.) lacking evidence of original authorship/ creative input of any kind. This
template should not be used if a more-specific suitable public domain copyright tag is available (e.g., the tag PD-chem for images
of chemical compounds or PD-textlogo for ineligible logos). However, the sweat-of-the-brow doctrine means that even complicated
images/ files may be ineligible for copyright protection so long as they consist solely of information and are utterly lacking in
originality and creativity— in that case, this tag may be appropriate." ]
Set Field [ tagTable::Ktitle1; 92020172311201501 ]
Set Field [ tagTable::Kpicture1; 92120171043101504 ]
#
#
#
#1b Share - public domain in some places, not all
New Record/Request
Set Field [ tagTable::kGroupOrTest; 8172011134941554 ]
Set Field [ tagTable::match; "copyright" ]
Set Field [ tagTable::orderOrLock; "lock" ]
Set Field [ tagTable::kRecordCreatorNode; "defaultCopyright" ]
#376
Set Field [ tagTable::_Number; 376 ]
Set Field [ tagTable::_Ltag; 9072011223903376 ]
Set Variable [ $tag; Value:"PD in USA — Public domain in the United States" ]
Set Field [ tagTable::tag; $tag ]
Set Field [ tagTable::tagSpelling; $tag ]
Set Field [ tagTable::notesOrCopyright; ¶ &
TextSize ( TextColor ( TextFont ( "[NOTE: Click the 'web' button above to view the most current and complete source of the text
excerpts below, copied on September 22, 2017 from commons.wikimedia.org/wiki/Template:PD-US for your convenience.]" & ¶ ;
"Arial" ) ; RGB ( 51 ; 51 ; 51 ) ) ; 16 )
& ¶ &
TextStyleAdd ( "Template:PD-US" ; Bold )
& ¶ & ¶ &
"This media file is in the public domain in the United States."
& ¶ & ¶ &
"This applies to U.S. works where the copyright has expired, often because its first publication occurred prior to January 1, 1923."
& ¶ & ¶ &
"This image might not be in the public domain outside of the United States; this especially applies in the countries and areas that
do not apply the rule of the shorter term for US works, such as Canada, Mainland China (not Hong Kong or Macao), Germany,
Mexico, and Switzerland. The creator and year of publication are essential information and must be provided. See Wikipedia:
Public domain and Wikipedia:Copyrights for more details." ]
Set Field [ tagTable::Ktitle1; 121920161421511408 ]
Set Field [ tagTable::Kpicture1; 92120171043101504 ]
#
#1b Share - public domain in some places, not all
New Record/Request
Set Field [ tagTable::kGroupOrTest; 8172011134941554 ]
Set Field [ tagTable::match; "copyright" ]
Set Field [ tagTable::orderOrLock; "lock" ]
Set Field [ tagTable::kRecordCreatorNode; "defaultCopyright" ]
#374
Set Field [ tagTable::_Number; 374 ]
Set Field [ tagTable::_Ltag; 9072011221202374 ]
Set Variable [ $tag; Value:"PD 70 — Public domain in country of origin where copyright term is the author's life plus 70 years or less." ]
Set Field [ tagTable::tag; $tag ]
Set Field [ tagTable::tagSpelling; $tag ]
Set Field [ tagTable::notesOrCopyright; ¶ &
TextSize ( TextColor ( TextFont ( "[NOTE: Click the 'web' button above to view the most current and complete source of the text
excerpts below, copied on September 22, 2017 from commons.wikimedia.org/wiki/Template:PD-old for your convenience.]" & ¶ ;
"Arial" ) ; RGB ( 51 ; 51 ; 51 ) ) ; 16 )
& ¶ &
TextStyleAdd ( "Template:PD-old" ; Bold )
& ¶ & ¶ &
"This work is in the public domain in its country of origin and other countries and areas where the copyright term is the author's life
plus 70 years or less.
" & ¶ & ¶ &
"You must also include a United States public domain tag to indicate why this work is in the public domain in the United States.
Note that a few countries have copyright terms longer than 70 years: Mexico has 100 years, Jamaica has 95 years, Colombia has
80 years, and Guatemala and Samoa have 75 years. This image may not be in the public domain in these countries, which
moreover do not implement the rule of the shorter term. Côte d'Ivoire has a general copyright term of 99 years and Honduras has
75 years, but they do implement the rule of the shorter term. Copyright may extend on works created by French who died for
France in World War II (more information), Russians who served in the Eastern Front of World War II (known as the Great Patriotic
War in Russia) and posthumously rehabilitated victims of Soviet repressions (more information)." ]
Set Field [ tagTable::Ktitle1; 121920161534521409 ]
Set Field [ tagTable::Kpicture1; 92120171043101504 ]
#
#1b Share - public domain in some places, not all
New Record/Request
Set Field [ tagTable::kGroupOrTest; 8172011134941554 ]
Set Field [ tagTable::match; "copyright" ]
Set Field [ tagTable::orderOrLock; "lock" ]
Set Field [ tagTable::kRecordCreatorNode; "defaultCopyright" ]
#1278
Set Field [ tagTable::_Number; 1278 ]
Set Field [ tagTable::_Ltag; 42420122157181278 ]
Set Variable [ $tag; Value:"PD Title 17 — Public domain in the United States because it is a work prepared by an officer or employee of
the United States Government as part of that person’s official duties under the terms of Title 17, Chapter 1, Section 105 of the US
Code." ]
Set Field [ tagTable::tag; $tag ]
Set Field [ tagTable::tagSpelling; $tag ]
Set Field [ tagTable::notesOrCopyright; ¶ &
TextSize ( TextColor ( TextFont ( "[NOTE: Click the 'web' button above to view the most current and complete source of the text
excerpts below, copied on September 22, 2017 from commons.wikimedia.org/wiki/Template:PD-USGov for your convenience.]" &
¶ ; "Arial" ) ; RGB ( 51 ; 51 ; 51 ) ) ; 16 )
& ¶ &
TextStyleAdd ( "Template:PD-USGov" ; Bold )
& ¶ & ¶ &
"This work is in the public domain in the United States because it is a work prepared by an officer or employee of the United States
Government as part of that person’s official duties under the terms of Title 17, Chapter 1, Section 105 of the US Code. See
Copyright."
& ¶ & ¶ &
"Note: This only applies to original works of the Federal Government and not to the work of any individual U.S. state, territory,
commonwealth, county, municipality, or any other subdivision. This template also does not apply to postage stamp designs
published by the United States Postal Service since 1978. (See § 313.6(C)(1) of Compendium of U.S. Copyright Office Practices).
It also does not apply to certain US coins; see The US Mint Terms of Use." ]
Set Field [ tagTable::Ktitle1; 121920161625111411 ]
Set Field [ tagTable::Kpicture1; 92120171043101504 ]
#
#
#
#2 Share and give credit CC BY
New Record/Request
Set Field [ tagTable::kGroupOrTest; 31620121746441302 ]
Set Field [ tagTable::match; "copyright" ]
Set Field [ tagTable::orderOrLock; "lock" ]
Set Field [ tagTable::kRecordCreatorNode; "defaultCopyright" ]
#1229
Set Field [ tagTable::_Number; 1229 ]
Set Field [ tagTable::_Ltag; 31620121746441229 ]
Set Variable [ $tag; Value:"CC By 3.0 — Creative Commons Attribution 3.0 Unported" ]
Set Field [ tagTable::tag; $tag ]
Set Field [ tagTable::tagSpelling; $tag ]
Set Field [ tagTable::notesOrCopyright; ¶ &
TextSize ( TextColor ( TextFont ( "[NOTE: Click the 'web' button above to view the most current and complete source of the text
below, copied on September 22, 2017 from creativecommons.org/licenses/by/3.0/ for your convenience.]" & ¶ ; "Arial" ) ; RGB
( 51 ; 51 ; 51 ) ) ; 16 )
& ¶ &
TextStyleAdd ( "Attribution 3.0 Unported (CC BY 3.0) " ; Bold )
& ¶ & ¶ &
"This is a human-readable summary of the Legal Code (read the full text). Disclaimer"
& ¶ & ¶ &
TextStyleAdd ( "You are free to:" ; Bold )
& ¶ & ¶ &
TextStyleAdd ( "Share" ; Bold ) & " — copy and redistribute the material in any medium or format"
& ¶ & ¶ &
TextStyleAdd ( "Adapt" ; Bold ) & " — remix, transform, and build upon the material
for any purpose, even commercially. "
& ¶ & ¶ &
"The licensor cannot revoke these freedoms as long as you follow the license terms."
& ¶ & ¶ &
TextStyleAdd ( "Under the following terms:" ; Bold )
& ¶ & ¶ &
TextStyleAdd ( "Attribution" ; Bold ) & " — You must give appropriate credit, provide a link to the license, and indicate if changes
were made. You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use."
& ¶ & ¶ &
TextStyleAdd ( "No additional restrictions" ; Bold ) & " — You may not apply legal terms or technological measures that legally
restrict others from doing anything the license permits."
& ¶ & ¶ &
TextStyleAdd ( "Notices:" ; Bold )
& ¶ & ¶ &
"You do not have to comply with the license for elements of the material in the public domain or where your use is permitted by an
applicable exception or limitation."
& ¶ & ¶ &
"No warranties are given. The license may not give you all of the permissions necessary for your intended use. For example, other
rights such as publicity, privacy, or moral rights may limit how you use the material." ]
Set Field [ tagTable::Ktitle1; 1122012154502117 ]
Set Field [ tagTable::Kpicture1; 92020171106021484 ]
#
#2 Share and give credit CC BY
New Record/Request
Set Field [ tagTable::kGroupOrTest; 31620121746441302 ]
Set Field [ tagTable::match; "copyright" ]
Set Field [ tagTable::orderOrLock; "lock" ]
Set Field [ tagTable::kRecordCreatorNode; "defaultCopyright" ]
#904
Set Field [ tagTable::_Number; 904 ]
Set Field [ tagTable::_Ltag; 6282014220454904 ]
Set Variable [ $tag; Value:"CC By 4.0 — Creative Commons Attribution 4.0 International" ]
Set Field [ tagTable::tag; $tag ]
Set Field [ tagTable::tagSpelling; $tag ]
Set Field [ tagTable::notesOrCopyright; ¶ &
TextSize ( TextColor ( TextFont ( "[NOTE: Click the 'web' button above to view the most current and complete source of the text
below, copied on September 22, 2017 from creativecommons.org/licenses/by/4.0/ for your convenience.]" & ¶ ; "Arial" ) ; RGB
( 51 ; 51 ; 51 ) ) ; 16 )
& ¶ &
TextStyleAdd ( "Attribution 4.0 International (CC BY 4.0) " ; Bold )
& ¶ & ¶ &
"This is a human-readable summary of the Legal Code (read the full text). Disclaimer"
& ¶ & ¶ &
TextStyleAdd ( "You are free to:" ; Bold )
& ¶ & ¶ &
TextStyleAdd ( "Share" ; Bold ) & " — copy and redistribute the material in any medium or format"
& ¶ & ¶ &
TextStyleAdd ( "Adapt" ; Bold ) & " — remix, transform, and build upon the material
for any purpose, even commercially. "
& ¶ & ¶ &
"The licensor cannot revoke these freedoms as long as you follow the license terms."
& ¶ & ¶ &
TextStyleAdd ( "Under the following terms:" ; Bold )
& ¶ & ¶ &
TextStyleAdd ( "Attribution" ; Bold ) & " — You must give appropriate credit, provide a link to the license, and indicate if changes
were made. You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use."
& ¶ & ¶ &
TextStyleAdd ( "No additional restrictions" ; Bold ) & " — You may not apply legal terms or technological measures that legally
restrict others from doing anything the license permits."
& ¶ & ¶ &
TextStyleAdd ( "Notices:" ; Bold )
& ¶ & ¶ &
"You do not have to comply with the license for elements of the material in the public domain or where your use is permitted by an
applicable exception or limitation."
& ¶ & ¶ &
"No warranties are given. The license may not give you all of the permissions necessary for your intended use. For example, other
rights such as publicity, privacy, or moral rights may limit how you use the material." ]
Set Field [ tagTable::Ktitle1; 62820142202121325 ]
Set Field [ tagTable::Kpicture1; 92020171106021484 ]
#
#
#
#3 Share, give credit, and use the same copyright license CC BY-SA
New Record/Request
Set Field [ tagTable::kGroupOrTest; 31620121841541305 ]
Set Field [ tagTable::match; "copyright" ]
Set Field [ tagTable::orderOrLock; "lock" ]
Set Field [ tagTable::kRecordCreatorNode; "defaultCopyright" ]
#1232
Set Field [ tagTable::_Number; 1232 ]
Set Field [ tagTable::_Ltag; 31620121841541232 ]
Set Variable [ $tag; Value:"CC By SA 3.0 — Creative Commons Attribution-ShareAlike 3.0 Unported" ]
Set Field [ tagTable::tag; $tag ]
Set Field [ tagTable::tagSpelling; $tag ]
Set Field [ tagTable::notesOrCopyright; ¶ &
TextSize ( TextColor ( TextFont ( "[NOTE: Click the 'web' button above to view the most current and complete source of the text
below, copied on September 22, 2017 from creativecommons.org/licenses/by-sa/3.0/ for your convenience.]" & ¶ ; "Arial" ) ; RGB
( 51 ; 51 ; 51 ) ) ; 16 )
& ¶ &
TextStyleAdd ( "Attribution-ShareAlike 3.0 Unported (CC BY-SA 3.0)" ; Bold )
& ¶ & ¶ &
"This is a human-readable summary of the Legal Code (read the full text). Disclaimer"
& ¶ & ¶ &
TextStyleAdd ( "You are free to:" ; Bold )
& ¶ & ¶ &
TextStyleAdd ( "Share" ; Bold ) & " — copy and redistribute the material in any medium or format"
& ¶ & ¶ &
TextStyleAdd ( "Adapt" ; Bold ) & " — remix, transform, and build upon the material
for any purpose, even commercially. "
& ¶ & ¶ &
"The licensor cannot revoke these freedoms as long as you follow the license terms."
& ¶ & ¶ &
TextStyleAdd ( "Under the following terms:" ; Bold )
& ¶ & ¶ &
TextStyleAdd ( "Attribution" ; Bold ) & " — You must give appropriate credit, provide a link to the license, and indicate if changes
were made. You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use."
& ¶ & ¶ &
TextStyleAdd ( "ShareAlike" ; Bold ) & " — If you remix, transform, or build upon the material, you must distribute your
contributions under the same license as the original."
& ¶ & ¶ &
TextStyleAdd ( "No additional restrictions" ; Bold ) & " — You may not apply legal terms or technological measures that legally
restrict others from doing anything the license permits."
& ¶ & ¶ &
TextStyleAdd ( "Notices:" ; Bold )
& ¶ & ¶ &
"You do not have to comply with the license for elements of the material in the public domain or where your use is permitted by an
applicable exception or limitation."
& ¶ & ¶ &
"No warranties are given. The license may not give you all of the permissions necessary for your intended use. For example, other
rights such as publicity, privacy, or moral rights may limit how you use the material." ]
Set Field [ tagTable::Ktitle1; 1122012155338120 ]
Set Field [ tagTable::Kpicture1; 92020172247301499 ]
#
#3 Share, give credit, and use the same copyright license CC BY-SA
New Record/Request
Set Field [ tagTable::kGroupOrTest; 31620121841541305 ]
Set Field [ tagTable::match; "copyright" ]
Set Field [ tagTable::orderOrLock; "lock" ]
Set Field [ tagTable::kRecordCreatorNode; "defaultCopyright" ]
#905
Set Field [ tagTable::_Number; 905 ]
Set Field [ tagTable::_Ltag; 6282014225223905 ]
Set Variable [ $tag; Value:"CC By SA 4.0 — Creative Commons Attribution-ShareAlike 4.0 International" ]
Set Field [ tagTable::tag; $tag ]
Set Field [ tagTable::tagSpelling; $tag ]
Set Field [ tagTable::notesOrCopyright; ¶ &
TextSize ( TextColor ( TextFont ( "[NOTE: Click the 'web' button above to view the most current and complete source of the text
below, copied on September 22, 2017 from creativecommons.org/licenses/by-sa/4.0/ for your convenience.]" & ¶ ; "Arial" ) ; RGB
( 51 ; 51 ; 51 ) ) ; 16 )
& ¶ &
TextStyleAdd ( "Attribution-ShareAlike 4.0 International (CC BY-SA 4.0)" ; Bold )
& ¶ & ¶ &
"This is a human-readable summary of the Legal Code (read the full text). Disclaimer"
& ¶ & ¶ &
TextStyleAdd ( "You are free to:" ; Bold )
& ¶ & ¶ &
TextStyleAdd ( "Share" ; Bold ) & " — copy and redistribute the material in any medium or format"
& ¶ & ¶ &
TextStyleAdd ( "Adapt" ; Bold ) & " — remix, transform, and build upon the material
for any purpose, even commercially. "
& ¶ & ¶ &
"The licensor cannot revoke these freedoms as long as you follow the license terms."
& ¶ & ¶ &
TextStyleAdd ( "Under the following terms:" ; Bold )
& ¶ & ¶ &
TextStyleAdd ( "Attribution" ; Bold ) & " — You must give appropriate credit, provide a link to the license, and indicate if changes
were made. You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use."
& ¶ & ¶ &
TextStyleAdd ( "ShareAlike" ; Bold ) & " — If you remix, transform, or build upon the material, you must distribute your
contributions under the same license as the original."
& ¶ & ¶ &
TextStyleAdd ( "No additional restrictions" ; Bold ) & " — You may not apply legal terms or technological measures that legally
restrict others from doing anything the license permits."
& ¶ & ¶ &
TextStyleAdd ( "Notices:" ; Bold )
& ¶ & ¶ &
"You do not have to comply with the license for elements of the material in the public domain or where your use is permitted by an
applicable exception or limitation."
& ¶ & ¶ &
"No warranties are given. The license may not give you all of the permissions necessary for your intended use. For example, other
rights such as publicity, privacy, or moral rights may limit how you use the material." ]
Set Field [ tagTable::Ktitle1; 62820142252121331 ]
Set Field [ tagTable::Kpicture1; 92020172247301499 ]
#
#
#
#4 Share, give credit, and don’t change CC BY-ND
New Record/Request
Set Field [ tagTable::kGroupOrTest; 31620121902441307 ]
Set Field [ tagTable::match; "copyright" ]
Set Field [ tagTable::orderOrLock; "lock" ]
Set Field [ tagTable::kRecordCreatorNode; "defaultCopyright" ]
#1234
Set Field [ tagTable::_Number; 1234 ]
Set Field [ tagTable::_Ltag; 31620121902441234 ]
Set Variable [ $tag; Value:"CC By ND 3.0 — Creative Commons Attribution-NoDerivs 3.0 Unported" ]
Set Field [ tagTable::tag; $tag ]
Set Field [ tagTable::tagSpelling; $tag ]
Set Field [ tagTable::notesOrCopyright; ¶ &
TextSize ( TextColor ( TextFont ( "[NOTE: Click the 'web' button above to view the most current and complete source of the text
below, copied on September 22, 2017 from creativecommons.org/licenses/by-nd/3.0/ for your convenience.]" & ¶ ; "Arial" ) ; RGB
( 51 ; 51 ; 51 ) ) ; 16 )
& ¶ &
TextStyleAdd ( "Attribution-ShareAlike 3.0 Unported (CC BY-SA 3.0)" ; Bold )
& ¶ & ¶ &
"This is a human-readable summary of the Legal Code (read the full text). Disclaimer"
& ¶ & ¶ &
TextStyleAdd ( "You are free to:" ; Bold )
& ¶ & ¶ &
TextStyleAdd ( "Share" ; Bold ) & " — copy and redistribute the material in any medium or format for any purpose, even
commercially. "
& ¶ & ¶ &
"The licensor cannot revoke these freedoms as long as you follow the license terms."
& ¶ & ¶ &
TextStyleAdd ( "Under the following terms:" ; Bold )
& ¶ & ¶ &
TextStyleAdd ( "Attribution" ; Bold ) & " — You must give appropriate credit, provide a link to the license, and indicate if changes
were made. You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use."
& ¶ & ¶ &
TextStyleAdd ( "NoDerivatives" ; Bold ) & " — If you remix, transform, or build upon the material, you may not distribute the
modified material."
& ¶ & ¶ &
TextStyleAdd ( "No additional restrictions" ; Bold ) & " — You may not apply legal terms or technological measures that legally
restrict others from doing anything the license permits."
& ¶ & ¶ &
TextStyleAdd ( "Notices:" ; Bold )
& ¶ & ¶ &
"You do not have to comply with the license for elements of the material in the public domain or where your use is permitted by an
applicable exception or limitation."
& ¶ & ¶ &
"No warranties are given. The license may not give you all of the permissions necessary for your intended use. For example, other
rights such as publicity, privacy, or moral rights may limit how you use the material." ]
Set Field [ tagTable::Ktitle1; 3162012190014146 ]
Set Field [ tagTable::Kpicture1; 92020172209091494 ]
#This field must be set to get copyright tags to
#sort so that the 3.0 ND tag comes before the
#4.0 ND tag as it does for all the other Creative
#Commons tags.
Set Field [ tagTable::textStyleOrCreatorNodeFlag; 1 ]
#
#4 Share, give credit, and don’t change CC BY-ND
New Record/Request
Set Field [ tagTable::kGroupOrTest; 31620121902441307 ]
Set Field [ tagTable::match; "copyright" ]
Set Field [ tagTable::orderOrLock; "lock" ]
Set Field [ tagTable::kRecordCreatorNode; "defaultCopyright" ]
#908
Set Field [ tagTable::_Number; 908 ]
Set Field [ tagTable::_Ltag; 6282014232807908 ]
Set Variable [ $tag; Value:"CC By ND 4.0 — Creative Commons Attribution-NoDerivatives 4.0 International" ]
Set Field [ tagTable::tag; $tag ]
Set Field [ tagTable::tagSpelling; $tag ]
Set Field [ tagTable::notesOrCopyright; ¶ &
TextSize ( TextColor ( TextFont ( "[NOTE: Click the 'web' button above to view the most current and complete source of the text
below, copied on September 22, 2017 from creativecommons.org/licenses/by-nd/4.0/ for your convenience.]" & ¶ ; "Arial" ) ; RGB
( 51 ; 51 ; 51 ) ) ; 16 )
& ¶ &
TextStyleAdd ( "Attribution-NoDerivatives 4.0 International (CC BY-ND 4.0)" ; Bold )
& ¶ & ¶ &
"This is a human-readable summary of the Legal Code (read the full text). Disclaimer"
& ¶ & ¶ &
TextStyleAdd ( "You are free to:" ; Bold )
& ¶ & ¶ &
TextStyleAdd ( "Share" ; Bold ) & " — copy and redistribute the material in any medium or format for any purpose, even
commercially. "
& ¶ & ¶ &
"The licensor cannot revoke these freedoms as long as you follow the license terms."
& ¶ & ¶ &
TextStyleAdd ( "Under the following terms:" ; Bold )
& ¶ & ¶ &
TextStyleAdd ( "Attribution" ; Bold ) & " — You must give appropriate credit, provide a link to the license, and indicate if changes
were made. You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use."
& ¶ & ¶ &
TextStyleAdd ( "NoDerivatives" ; Bold ) & " — If you remix, transform, or build upon the material, you may not distribute the
modified material."
& ¶ & ¶ &
TextStyleAdd ( "No additional restrictions" ; Bold ) & " — You may not apply legal terms or technological measures that legally
restrict others from doing anything the license permits."
& ¶ & ¶ &
TextStyleAdd ( "Notices:" ; Bold )
& ¶ & ¶ &
"You do not have to comply with the license for elements of the material in the public domain or where your use is permitted by an
applicable exception or limitation."
& ¶ & ¶ &
"No warranties are given. The license may not give you all of the permissions necessary for your intended use. For example, other
rights such as publicity, privacy, or moral rights may limit how you use the material." ]
Set Field [ tagTable::Ktitle1; 62820142328311335 ]
Set Field [ tagTable::Kpicture1; 92020172209091494 ]
#This field must be set to get copyright tags to
#sort so that the 3.0 ND tag comes before the
#4.0 ND tag as it does for all the other Creative
#Commons tags.
Set Field [ tagTable::textStyleOrCreatorNodeFlag; 2 ]
#
#
#
#5 Share, give credit, and don’t sell CC BY-NC
New Record/Request
Set Field [ tagTable::kGroupOrTest; 31620121837161304 ]
Set Field [ tagTable::match; "copyright" ]
Set Field [ tagTable::orderOrLock; "lock" ]
Set Field [ tagTable::kRecordCreatorNode; "defaultCopyright" ]
#1231
Set Field [ tagTable::_Number; 1231 ]
Set Field [ tagTable::_Ltag; 31620121837161231 ]
Set Variable [ $tag; Value:"CC By NC 3.0 — Creative Commons Attribution-NonCommercial 3.0 Unported" ]
Set Field [ tagTable::tag; $tag ]
Set Field [ tagTable::tagSpelling; $tag ]
Set Field [ tagTable::notesOrCopyright; ¶ &
TextSize ( TextColor ( TextFont ( "[NOTE: Click the 'web' button above to view the most current and complete source of the text
below, copied on September 22, 2017 from creativecommons.org/licenses/by-nc/3.0/ for your convenience.]" & ¶ ; "Arial" ) ; RGB
( 51 ; 51 ; 51 ) ) ; 16 )
& ¶ &
TextStyleAdd ( "Attribution-NonCommercial 3.0 Unported (CC BY-NC 3.0)" ; Bold )
& ¶ & ¶ &
"This is a human-readable summary of the Legal Code (read the full text). Disclaimer"
& ¶ & ¶ &
TextStyleAdd ( "You are free to:" ; Bold )
& ¶ & ¶ &
TextStyleAdd ( "Share" ; Bold ) & " — copy and redistribute the material in any medium or format "
& ¶ & ¶ &
TextStyleAdd ( "Adapt" ; Bold ) & " — remix, transform, and build upon the material"
& ¶ & ¶ &
"The licensor cannot revoke these freedoms as long as you follow the license terms."
& ¶ & ¶ &
TextStyleAdd ( "Under the following terms:" ; Bold )
& ¶ & ¶ &
TextStyleAdd ( "Attribution" ; Bold ) & " — You must give appropriate credit, provide a link to the license, and indicate if changes
were made. You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use."
& ¶ & ¶ &
TextStyleAdd ( "NonCommercial" ; Bold ) & " — You may not use the material for commercial purposes."
& ¶ & ¶ &
TextStyleAdd ( "No additional restrictions" ; Bold ) & " — You may not apply legal terms or technological measures that legally
restrict others from doing anything the license permits."
& ¶ & ¶ &
TextStyleAdd ( "Notices:" ; Bold )
& ¶ & ¶ &
"You do not have to comply with the license for elements of the material in the public domain or where your use is permitted by an
applicable exception or limitation."
& ¶ & ¶ &
"No warranties are given. The license may not give you all of the permissions necessary for your intended use. For example, other
rights such as publicity, privacy, or moral rights may limit how you use the material." ]
Set Field [ tagTable::Ktitle1; 1122012155421121 ]
Set Field [ tagTable::Kpicture1; 92020172214211498 ]
#
#5 Share, give credit, and don’t sell CC BY-NC
New Record/Request
Set Field [ tagTable::kGroupOrTest; 31620121837161304 ]
Set Field [ tagTable::match; "copyright" ]
Set Field [ tagTable::orderOrLock; "lock" ]
Set Field [ tagTable::kRecordCreatorNode; "defaultCopyright" ]
#903
Set Field [ tagTable::_Number; 903 ]
Set Field [ tagTable::_Ltag; 6272014222057903 ]
Set Variable [ $tag; Value:"CC By NC 4.0 — Creative Commons Attribution-NonCommercial 4.0 International" ]
Set Field [ tagTable::tag; $tag ]
Set Field [ tagTable::tagSpelling; $tag ]
Set Field [ tagTable::notesOrCopyright; ¶ &
TextSize ( TextColor ( TextFont ( "[NOTE: Click the 'web' button above to view the most current and complete source of the text
below, copied on September 22, 2017 from creativecommons.org/licenses/by-nc/4.0/ for your convenience.]" & ¶ ; "Arial" ) ; RGB
( 51 ; 51 ; 51 ) ) ; 16 )
& ¶ &
TextStyleAdd ( "Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)" ; Bold )
& ¶ & ¶ &
"This is a human-readable summary of the Legal Code (read the full text). Disclaimer"
& ¶ & ¶ &
TextStyleAdd ( "You are free to:" ; Bold )
& ¶ & ¶ &
TextStyleAdd ( "Share" ; Bold ) & " — copy and redistribute the material in any medium or format "
& ¶ & ¶ &
TextStyleAdd ( "Adapt" ; Bold ) & " — remix, transform, and build upon the material"
& ¶ & ¶ &
"The licensor cannot revoke these freedoms as long as you follow the license terms."
& ¶ & ¶ &
TextStyleAdd ( "Under the following terms:" ; Bold )
& ¶ & ¶ &
TextStyleAdd ( "Attribution" ; Bold ) & " — You must give appropriate credit, provide a link to the license, and indicate if changes
were made. You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use."
& ¶ & ¶ &
TextStyleAdd ( "NonCommercial" ; Bold ) & " — You may not use the material for commercial purposes."
& ¶ & ¶ &
TextStyleAdd ( "No additional restrictions" ; Bold ) & " — You may not apply legal terms or technological measures that legally
restrict others from doing anything the license permits."
& ¶ & ¶ &
TextStyleAdd ( "Notices:" ; Bold )
& ¶ & ¶ &
"You do not have to comply with the license for elements of the material in the public domain or where your use is permitted by an
applicable exception or limitation."
& ¶ & ¶ &
"No warranties are given. The license may not give you all of the permissions necessary for your intended use. For example, other
rights such as publicity, privacy, or moral rights may limit how you use the material." ]
Set Field [ tagTable::Ktitle1; 62820142355431336 ]
Set Field [ tagTable::Kpicture1; 92020172214211498 ]
#
#
#
#6 Share, give credit, don’t sell, and use the same copyright license CC BY-NC-SA
New Record/Request
Set Field [ tagTable::kGroupOrTest; 8162011231825553 ]
Set Field [ tagTable::match; "copyright" ]
Set Field [ tagTable::orderOrLock; "lock" ]
Set Field [ tagTable::kRecordCreatorNode; "defaultCopyright" ]
#326
Set Field [ tagTable::_Number; 326 ]
Set Field [ tagTable::_Ltag; 8162011231825326 ]
Set Variable [ $tag; Value:"CC By NC SA 3.0 — Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported" ]
Set Field [ tagTable::tag; $tag ]
Set Field [ tagTable::tagSpelling; $tag ]
Set Field [ tagTable::notesOrCopyright; ¶ &
TextSize ( TextColor ( TextFont ( "[NOTE: Click the 'web' button above to view the most current and complete source of the text
below, copied on September 22, 2017 from creativecommons.org/licenses/by-nc-sa/3.0/ for your convenience.]" & ¶ ; "Arial" ) ;
RGB ( 51 ; 51 ; 51 ) ) ; 16 )
& ¶ &
TextStyleAdd ( "Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)" ; Bold )
& ¶ & ¶ &
"This is a human-readable summary of the Legal Code (read the full text). Disclaimer"
& ¶ & ¶ &
TextStyleAdd ( "You are free to:" ; Bold )
& ¶ & ¶ &
TextStyleAdd ( "Share" ; Bold ) & " — copy and redistribute the material in any medium or format "
& ¶ & ¶ &
TextStyleAdd ( "Adapt" ; Bold ) & " — remix, transform, and build upon the material"
& ¶ & ¶ &
"The licensor cannot revoke these freedoms as long as you follow the license terms."
& ¶ & ¶ &
TextStyleAdd ( "Under the following terms:" ; Bold )
& ¶ & ¶ &
TextStyleAdd ( "Attribution" ; Bold ) & " — You must give appropriate credit, provide a link to the license, and indicate if changes
were made. You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use."
& ¶ & ¶ &
TextStyleAdd ( "NonCommercial" ; Bold ) & " — You may not use the material for commercial purposes."
& ¶ & ¶ &
TextStyleAdd ( "ShareAlike" ; Bold ) & " — If you remix, transform, or build upon the material, you must distribute your
contributions under the same license as the original. "
& ¶ & ¶ &
TextStyleAdd ( "No additional restrictions" ; Bold ) & " — You may not apply legal terms or technological measures that legally
restrict others from doing anything the license permits."
& ¶ & ¶ &
TextStyleAdd ( "Notices:" ; Bold )
& ¶ & ¶ &
"You do not have to comply with the license for elements of the material in the public domain or where your use is permitted by an
applicable exception or limitation."
& ¶ & ¶ &
"No warranties are given. The license may not give you all of the permissions necessary for your intended use. For example, other
rights such as publicity, privacy, or moral rights may limit how you use the material." ]
Set Field [ tagTable::Ktitle1; 1122012000717114 ]
Set Field [ tagTable::Kpicture1; 92020172213531497 ]
#
#6 Share, give credit, don’t sell, and use the same copyright license CC BY-NC-SA
New Record/Request
Set Field [ tagTable::kGroupOrTest; 8162011231825553 ]
Set Field [ tagTable::match; "copyright" ]
Set Field [ tagTable::orderOrLock; "lock" ]
Set Field [ tagTable::kRecordCreatorNode; "defaultCopyright" ]
#906
Set Field [ tagTable::_Number; 906 ]
Set Field [ tagTable::_Ltag; 6282014225704906 ]
Set Variable [ $tag; Value:"CC By NC SA 4.0 — Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International" ]
Set Field [ tagTable::tag; $tag ]
Set Field [ tagTable::tagSpelling; $tag ]
Set Field [ tagTable::notesOrCopyright; ¶ &
TextSize ( TextColor ( TextFont ( "[NOTE: Click the 'web' button above to view the most current and complete source of the text
below, copied on September 22, 2017 from creativecommons.org/licenses/by-nc-sa/4.0/ for your convenience.]" & ¶ ; "Arial" ) ;
RGB ( 51 ; 51 ; 51 ) ) ; 16 )
& ¶ &
TextStyleAdd ( "Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)" ; Bold )
& ¶ & ¶ &
"This is a human-readable summary of the Legal Code (read the full text). Disclaimer"
& ¶ & ¶ &
TextStyleAdd ( "You are free to:" ; Bold )
& ¶ & ¶ &
TextStyleAdd ( "Share" ; Bold ) & " — copy and redistribute the material in any medium or format "
& ¶ & ¶ &
TextStyleAdd ( "Adapt" ; Bold ) & " — remix, transform, and build upon the material"
& ¶ & ¶ &
"The licensor cannot revoke these freedoms as long as you follow the license terms."
& ¶ & ¶ &
TextStyleAdd ( "Under the following terms:" ; Bold )
& ¶ & ¶ &
TextStyleAdd ( "Attribution" ; Bold ) & " — You must give appropriate credit, provide a link to the license, and indicate if changes
were made. You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use."
& ¶ & ¶ &
TextStyleAdd ( "NonCommercial" ; Bold ) & " — You may not use the material for commercial purposes."
& ¶ & ¶ &
TextStyleAdd ( "ShareAlike" ; Bold ) & " — If you remix, transform, or build upon the material, you must distribute your
contributions under the same license as the original. "
& ¶ & ¶ &
TextStyleAdd ( "No additional restrictions" ; Bold ) & " — You may not apply legal terms or technological measures that legally
restrict others from doing anything the license permits."
& ¶ & ¶ &
TextStyleAdd ( "Notices:" ; Bold )
& ¶ & ¶ &
"You do not have to comply with the license for elements of the material in the public domain or where your use is permitted by an
applicable exception or limitation."
& ¶ & ¶ &
"No warranties are given. The license may not give you all of the permissions necessary for your intended use. For example, other
rights such as publicity, privacy, or moral rights may limit how you use the material." ]
Set Field [ tagTable::Ktitle1; 62820142320251334 ]
Set Field [ tagTable::Kpicture1; 92020172213531497 ]
#
#
#
#7 Share, give credit, don’t sell, don't change = use the same copyright license CC BY-NC-ND
New Record/Request
Set Field [ tagTable::kGroupOrTest; 31620121824141303 ]
Set Field [ tagTable::match; "copyright" ]
Set Field [ tagTable::orderOrLock; "lock" ]
Set Field [ tagTable::kRecordCreatorNode; "defaultCopyright" ]
#1049
Set Field [ tagTable::_Number; 1049 ]
Set Field [ tagTable::_Ltag; 121620112002051049 ]
Set Variable [ $tag; Value:"CC By NC ND 3.0 — Creative Commons Attribution-NonCommercial-NoDerivs 3.0 Unported" ]
Set Field [ tagTable::tag; $tag ]
Set Field [ tagTable::tagSpelling; $tag ]
Set Field [ tagTable::notesOrCopyright; ¶ &
TextSize ( TextColor ( TextFont ( "[NOTE: Click the 'web' button above to view the most current and complete source of the text
below, copied on September 22, 2017 from creativecommons.org/licenses/by-nc-nd/3.0/ for your convenience.]" & ¶ ; "Arial" ) ;
RGB ( 51 ; 51 ; 51 ) ) ; 16 )
& ¶ &
TextStyleAdd ( "Attribution-NonCommercial-NoDerivs 3.0 Unported (CC BY-NC-ND 3.0)" ; Bold )
& ¶ & ¶ &
"This is a human-readable summary of the Legal Code (read the full text). Disclaimer"
& ¶ & ¶ &
TextStyleAdd ( "You are free to:" ; Bold )
& ¶ & ¶ &
TextStyleAdd ( "Share" ; Bold ) & " — copy and redistribute the material in any medium or format"
& ¶ & ¶ &
"The licensor cannot revoke these freedoms as long as you follow the license terms."
& ¶ & ¶ &
TextStyleAdd ( "Under the following terms:" ; Bold )
& ¶ & ¶ &
TextStyleAdd ( "Attribution" ; Bold ) & " — You must give appropriate credit, provide a link to the license, and indicate if changes
were made. You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use."
& ¶ & ¶ &
TextStyleAdd ( "NonCommercial" ; Bold ) & " — You may not use the material for commercial purposes."
& ¶ & ¶ &
TextStyleAdd ( "NoDerivatives" ; Bold ) & " — If you remix, transform, or build upon the material, you may not distribute the
modified material."
& ¶ & ¶ &
TextStyleAdd ( "No additional restrictions" ; Bold ) & " — You may not apply legal terms or technological measures that legally
restrict others from doing anything the license permits."
& ¶ & ¶ &
TextStyleAdd ( "Notices:" ; Bold )
& ¶ & ¶ &
"You do not have to comply with the license for elements of the material in the public domain or where your use is permitted by an
applicable exception or limitation."
& ¶ & ¶ &
"No warranties are given. The license may not give you all of the permissions necessary for your intended use. For example, other
rights such as publicity, privacy, or moral rights may limit how you use the material." ]
Set Field [ tagTable::Ktitle1; 1122012155517122 ]
Set Field [ tagTable::Kpicture1; 92020172144131485 ]
#This field must be set to get copyright tags to
#sort so that the 3.0 ND tag comes before the
#4.0 ND tag as it does for all the other Creative
#Commons tags.
Set Field [ tagTable::textStyleOrCreatorNodeFlag; 1 ]
#
#7 Share, give credit, don’t sell, don't change = use the same copyright license CC BY-NC-ND
New Record/Request
Set Field [ tagTable::kGroupOrTest; 31620121824141303 ]
Set Field [ tagTable::match; "copyright" ]
Set Field [ tagTable::orderOrLock; "lock" ]
Set Field [ tagTable::kRecordCreatorNode; "defaultCopyright" ]
#907
Set Field [ tagTable::_Number; 907 ]
Set Field [ tagTable::_Ltag; 6282014230310907 ]
Set Variable [ $tag; Value:"CC By NC ND 4.0 — Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International" ]
Set Field [ tagTable::tag; $tag ]
Set Field [ tagTable::tagSpelling; $tag ]
Set Field [ tagTable::notesOrCopyright; ¶ &
TextSize ( TextColor ( TextFont ( "[NOTE: Click the 'web' button above to view the most current and complete source of the text
below, copied on September 22, 2017 from creativecommons.org/licenses/by-nc-nd/4.0/ for your convenience.]" & ¶ ; "Arial" ) ;
RGB ( 51 ; 51 ; 51 ) ) ; 16 )
& ¶ &
TextStyleAdd ( "Attribution-NonCommercial-NoDerivatives 4.0 International (CC BY-NC-ND 4.0)" ; Bold )
& ¶ & ¶ &
"This is a human-readable summary of the Legal Code (read the full text). Disclaimer"
& ¶ & ¶ &
TextStyleAdd ( "You are free to:" ; Bold )
& ¶ & ¶ &
TextStyleAdd ( "Share" ; Bold ) & " — copy and redistribute the material in any medium or format"
& ¶ & ¶ &
"The licensor cannot revoke these freedoms as long as you follow the license terms."
& ¶ & ¶ &
TextStyleAdd ( "Under the following terms:" ; Bold )
& ¶ & ¶ &
TextStyleAdd ( "Attribution" ; Bold ) & " — You must give appropriate credit, provide a link to the license, and indicate if changes
were made. You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use."
& ¶ & ¶ &
TextStyleAdd ( "NonCommercial" ; Bold ) & " — You may not use the material for commercial purposes."
& ¶ & ¶ &
TextStyleAdd ( "NoDerivatives" ; Bold ) & " — If you remix, transform, or build upon the material, you may not distribute the
modified material."
& ¶ & ¶ &
TextStyleAdd ( "No additional restrictions" ; Bold ) & " — You may not apply legal terms or technological measures that legally
restrict others from doing anything the license permits."
& ¶ & ¶ &
TextStyleAdd ( "Notices:" ; Bold )
& ¶ & ¶ &
"You do not have to comply with the license for elements of the material in the public domain or where your use is permitted by an
applicable exception or limitation."
& ¶ & ¶ &
"No warranties are given. The license may not give you all of the permissions necessary for your intended use. For example, other
rights such as publicity, privacy, or moral rights may limit how you use the material." ]
Set Field [ tagTable::Ktitle1; 62820142257411332 ]
Set Field [ tagTable::Kpicture1; 92020172144131485 ]
#This field must be set to get copyright tags to
#sort so that the 3.0 ND tag comes before the
#4.0 ND tag as it does for all the other Creative
#Commons tags.
Set Field [ tagTable::textStyleOrCreatorNodeFlag; 2 ]
#
#
#
#8 Don’t share - personal use only
New Record/Request
Set Field [ tagTable::kGroupOrTest; 8102011220941540 ]
Set Field [ tagTable::match; "copyright" ]
Set Field [ tagTable::orderOrLock; "lock" ]
Set Field [ tagTable::kRecordCreatorNode; "defaultCopyright" ]
#282
Set Field [ tagTable::_Number; 282 ]
Set Field [ tagTable::_Ltag; 8102011220941282 ]
Set Variable [ $tag; Value:"© All rights reserved" ]
Set Field [ tagTable::tag; $tag ]
Set Field [ tagTable::tagSpelling; $tag ]
Set Field [ tagTable::notesOrCopyright; ¶ &
TextSize ( TextColor ( TextFont ( "[NOTE: Click the 'web' button above to view the most current and complete source of the text
excerpts below, copied on September 21, 2017 from en.wikipedia.org/wiki/Copyright_notice for your convenience.]" & ¶ ; "Arial" ) ;
RGB ( 51 ; 51 ; 51 ) ) ; 16 )
& ¶ &
TextStyleAdd ( "Copyright notice" ; Bold )
& ¶ & ¶ &
"This article is about the US statutorily-defined copyright notice. For notifications of claimed copyright infringement, see Online
Copyright Infringement Liability Limitation Act."
& ¶ & ¶ &
"..."
& ¶ & ¶ &
"In United States copyright law, a copyright notice is a notice of statutorily prescribed form that informs users of the underlying
claim to copyright ownership in a published work."
& ¶ & ¶ &
"Use of the notice informs the public that a work is protected by copyright, identifies the copyright owner, and shows the year of
first publication. Furthermore, in the event that a work is infringed, if the work carries a proper notice, the court will not give any
weight to a defendant’s use of an innocent infringement defense—that is, to a claim that the defendant did not realize that the work
was protected."
& ¶ & ¶ &
"For works first published on or after March 1, 1989, use of the copyright notice is optional. Before March 1, 1989, the use of the
notice was mandatory on all published works. Omitting the notice on any work first published from January 1, 1978, to February
28, 1989, could have resulted in the loss of copyright protection if corrective steps were not taken within a certain amount of time.
Works published before January 1, 1978, are governed by the 1909 Copyright Act. Under that law, if a work was published under
the copyright owner’s authority without a proper notice of copyright, all copyright protection for that work was permanently lost in
the United States."
& ¶ & ¶ &
"..."
& ¶ & ¶ &
TextStyleAdd ( "Form of notice for visually perceptible copies" ; Bold )
& ¶ & ¶ &
"1. The notice for visually perceptible copies should contain all three elements described below. They should appear together or in
close proximity on the copies."
& ¶ & ¶ &
"2. The symbol © (letter C in a circle); the word " & Quote ( "Copyright" ) & "; or the abbreviation " & Quote ( "Copr." )
& ¶ & ¶ &
"3. The year of first publication. If the work is a derivative work or a compilation incorporating previously published material, the
year date of first publication of the derivative work or compilation is sufficient. Examples of derivative works are translations or
dramatizations; an example of a compilation is an anthology. The year may be omitted when a pictorial, graphic, or sculptural
work, with accompanying textual matter, if any, is reproduced in or on greeting cards, postcards, stationery, jewelry, dolls, toys, or
useful articles."
& ¶ & ¶ &
"The name of the copyright owner, an abbreviation by which the name can be recognized, or a generally known alternative
designation of owner." ]
Set Field [ tagTable::Ktitle1; 62820142315491333 ]
Set Field [ tagTable::Kpicture1; 92120170936171502 ]
#
#
#
#Trademark, Service Mark, Logo, Etc.
New Record/Request
Set Field [ tagTable::kGroupOrTest; 92020171119521809 ]
Set Field [ tagTable::match; "copyright" ]
Set Field [ tagTable::orderOrLock; "lock" ]
Set Field [ tagTable::kRecordCreatorNode; "defaultCopyright" ]
#4454
Set Field [ tagTable::_Number; 4454 ]
Set Field [ tagTable::_Ltag; 92020171119524454 ]
Set Variable [ $tag; Value:"Trademark — Check owner's policy webpage for use and restrictions guidelines." ]
Set Field [ tagTable::tag; $tag ]
Set Field [ tagTable::tagSpelling; $tag ]
Set Field [ tagTable::notesOrCopyright; ¶ &
TextSize ( TextColor ( TextFont ( "[NOTE: Click the 'web' button above to view the most current and complete source of the text
excerpts below, copied on September 21, 2017 from en.wikipedia.org/wiki/Trademark for your convenience.]" & ¶ ; "Arial" ) ; RGB
( 51 ; 51 ; 51 ) ) ; 16 )
& ¶ &
TextStyleAdd ( "Trademark" ; Bold )
& ¶ & ¶ &
"A trademark, trade mark, or trade-mark[1] is a recognizable sign, design, or expression which identifies products or services of a
particular source from those of others,[2][3] although trademarks used to identify services are usually called service marks.[4][5]
The trademark owner can be an individual, business organization, or any legal entity. A trademark may be located on a package, a
label, a voucher, or on the product itself. For the sake of corporate identity, trademarks are often displayed on company buildings."
& ¶ & ¶ &
"..."
& ¶ & ¶ &
"The owner of a trademark may pursue legal action against trademark infringement. Most countries require formal registration of a
trademark as a precondition for pursuing this type of action. The United States, Canada and other countries also recognize
common law trademark rights, which means action can be taken to protect an unregistered trademark if it is in use. Still, common
law trademarks offer the holder in general less legal protection than registered trademarks."
& ¶ & ¶ &
"The term trademark is also used informally to refer to any distinguishing attribute by which an individual is readily identified, such
as the well-known characteristics of celebrities. When a trademark is used in relation to services rather than products, it may
sometimes be called a service mark, particularly in the United States.[7]"
& ¶ & ¶ &
"..."
& ¶ & ¶ &
TextStyleAdd ( "Terminology" ; Bold )
& ¶ & ¶ &
"... Terms such as " & Quote ( "mark" ) & ", " & Quote ( "brand" ) & " and " & Quote ( "trade" ) & " are sometimes used
interchangeably with " & Quote ( "trademark" ) & ". " & Quote ( "Trademark" ) & ", however, also includes any device, brand, label,
name, signature, word, letter, numerical, shape of goods, packaging, colour or combination of colours, smell, sound, movement or
any combination thereof which is capable of distinguishing goods and services of one business from those of others. It must be
capable of graphical representation and must be applied to goods or services for which it is registered."
& ¶ & ¶ &
"..."
& ¶ & ¶ &
TextStyleAdd ( "Comparison with patents, designs and copyright" ; Bold )
& ¶ & ¶ &
"... Trademarks, patents and designs collectively form a subset of intellectual property known as industrial property because they
are often created and used in an industrial or commercial context."
& ¶ & ¶ &
"By comparison, copyright law generally seeks to protect original literary, artistic and other creative works. Continued active use
and re-registration can make a trademark perpetual, whereas copyright usually lasts for the duration of the author's lifespan plus
70 years for works by individuals, and some limited time after creation for works by bodies corporate.[36] This can lead to
confusion in cases where a work passes into the public domain but the character in question remains a registered trademark."
& ¶ & ¶ &
"... Unlike patents and copyrights, which in theory are granted for one-off fixed terms, trademarks remain valid as long as the
owner actively uses and defends them and maintains their registrations with the competent authorities. This often involves
payment of a periodic renewal fee."
& ¶ & ¶ &
"As a trademark must be used to maintain rights in relation to that mark, a trademark can be 'abandoned' or its registration can be
cancelled or revoked if the mark is not continuously used. By comparison, patents and copyrights cannot be 'abandoned' and a
patent holder or copyright owner can generally enforce their rights without taking any particular action to maintain the patent or
copyright. Additionally, patent holders and copyright owners may not necessarily need to actively police their rights. " ]
Set Field [ tagTable::Ktitle1; 62820142315491333 ]
Set Field [ tagTable::Kpicture1; 92020172259191500 ]
#
#
Go to Field [ ]
#
#
