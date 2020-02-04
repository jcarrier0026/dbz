# dbz
Simple dbz game

## Development Setup
### Install SDL2 Dev Package
```bash
sudo apt-get install libsdl2-dev
sudo apt-get install libsdl2-image-dev
```

## Compilation Instructions
```bash
make
```

## Run Instructions
```bash
./dbz.out
```

## Development Tips

### Get the latest code
'develop' is the golden branch. Get the latest develop:
```bash
# Check out the develop branch
git checkout -b develop origin/develop # or just 'git checkout develop' if you already have a
develop branch

# Check that you're on the right branch
git status

# Check if anything changed on Github
git fetch

# Check if there are changes you need to pull down
git status

# Pull down any changes
git pull
```

### Start a feature branch
1. Create a feature branch associated with the github issue you're working on.
```bash
# Start a new feature branch based on develop.
git checkout -b feature/#<issue-number>-<name> origin/develop
```

2. Make changes to complete your feature.

3. Commit your changes.
```bash
# Check that the updated files look correct, and that you're on the right branch
git status

# Make sure the changes look good. This opens the changes in 'less'.
git diff

# Stage changes to existing files for commit.
git add -u

# Stage any new files for commit.
git add <new-file1> <new-file2>

# Make a commit. Write a descriptive commit message.
git commit

# Push your branch up to github for review.
git push -u origin <your-feature-branch-name>
```

4. Go to github and make a pull request to 'develop'

5. Make requested changes on your PR.

6. Push up your changes.
```bash
# Follow the instructions in #3 up to the 'git push' part.
# Push your changes to your remote branch.
git push
```

