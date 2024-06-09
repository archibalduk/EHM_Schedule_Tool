# EHM Schedule Tool
:rocket: A tool for generating schedule templates for Eastside Hockey Manager. :calendar:

Find more tools for Eastside Hockey Manager on [The Blue Line](https://ehmtheblueline.com).

# How to Install
1. Download and install [Microsoft Visual Studio 2022 Redistributable (x64 / 64-bit version)](https://aka.ms/vs/17/release/VC_redist.x64.exe) if you do not already have this installed;

1. Download the latest version of the Tool from the [Releases](https://github.com/archibalduk/EHM_Schedule_Tool/releases) page;

1. Extract the downloaded *.zip* file to a folder of your choice; and

1. Double-click on the downloaded *EHM Schedule Tool.exe* file to launch the Tool.

# How to Use
There are three ways in which schedule templates can be generated using the Tool:

1. From scratch by following the Tool's prompts *(Generate -> New schedule template)*;

1. From an existing schedule template *(File -> Open schedule template)*;

1. From an existing schedule matrix *(Generate -> New schedule template from matrix spreadsheet)*; or

1. From a text schedule *(File -> Open text schedule)*.

Step-by-step instructions are set out further below (see the *How to Generate a Schedule Template* section below).

The Tool also includes a few tool functions to tweak schedule templates (see the *Extra Tools* section below).

# Introduction
It is worth understanding a few basic concepts before using the Tool for the first time.

## What is a schedule template?
There are two types of schedule which can be assigned to a playable league in the EHM game database:

1. Schedule dates: This is essentially a list of dates from which the game will automatically generate a basic schedule. This can only be used for simpler league structures; it cannot generally be used for multi-conference/division setups.

1. Schedule templates: This is a fully custom schedule which must be created by hand. Each individual game must be listed out in the template; i.e. road club id, home club id and date. 

The Tool is intended to simplify the creation of schedule templates by automatically generating the schedule based on various custom parameters.

Schedule templates can be imported from a spreadsheet into an EHM database using the unofficial [EHM Editor](https://ehmtheblueline.com/editor) by Archibalduk.

Each club in a schedule template is represented by an id number in the following format: *[Division index][Club index]*

Each division of the playable league in question and as listed on the *Schedule Templates* screen of the EHM Editor is assigned an index number. The first division listed is 0 (zero), the second division is 1 (one), etc:

[Division index example](docs/img/division_index_example.png)

Each club within each division is allocated an index number based on the alphabetical order of each club. The first club within a division will have index 0 (zero), the second club will have index 1 (one), etc.

Here are some examples:

- 0000 = First division, first club within that division
- 0001 = First division, second club within that division
- 0100 = Second division, first club within that division
- 0101 = Second division, second club within that division
- 0205 = Third division, sixth club within that division
- 0206 = Third division, seventh club within that division

Note that zeros at the beginning of the club id values will be truncated when viewed in the Tool or Excel; e.g. 0001 will be shown as 1, 0205 will be shown as 205, etc.

Here are some example games within a schedule template:

| Road Club | Home Club | Day of Month | Month | Year Offset |
| ------------- | ------------- | | ------------- | | ------------- | | ------------- |
| 0 | 100 | 25 | 9 | 0 |
| 205 | 1 | 12 | 2 | 1 |

The Year Offset denotes in which year the game will occur relative to the in-game season. E.g. if the in-game season is 2024/25, a Year Offset of 0 (zero) means 2024 and a Year Offset of 1 (one) means 2025.

The first row in the example template above is decoded as follows:
- Road club id: 0 (i.e. 0000) = First division, first club within that division
- Home club id: 100 (i.e. 0100) = Second division, first club within that division
- Date: 25th day of the 9th month with Year Offset 0 = 25th of September of the year in which the season commences (e.g. 25-Sept-2024 for the 2024/25 season)

The second row in the example template above is decoded as follows:
- Road club id: 205 (i.e. 0205) = Third division, sixth club within that division
- Home club id: 1 (i.e. 0001) = First division, second club within that division
- Date: 12th day of the 2nd month with Year Offset 1 = 12th of February of the year after the season commences (e.g. 12-Feb-2025 for the 2024/25 season).

## What is a schedule matrix?

# How to Generate a Schedule Template

# Extra Tools

