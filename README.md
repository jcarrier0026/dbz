# dbz
Simple dbz game

## Development Setup
### Install SDL2 Dev Package
```bash
sudo apt-get install libsdl2-dev
```

## Compilation Instructions
```bash
g++ -lSDL2 main.cpp
```

## Run Instructions
```bash
./a.out
```

## Development Tips
### Start a feature branch
1. Create a feature branch associated with the github issue you're working on.
```bash
git checkout -b feature/#<issue-number>-<name>
```

2. Make changes to complete your feature.

3. Commit your changes.
```bash
git diff # Make sure the changes look good. This opens the changes in 'less'.
git add -u # commit changes to existing files
git add <new-file1> <new-file2>
git commit # Write a reasonable commit message.
git push -u origin <your-feature-branch-name>
```

4. Go to github and make a pull request to 'develop'

