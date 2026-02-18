import glob
import pandas as pd
from pathlib import Path
 
# list all csv files only
csv_files = glob.glob('output/*.{}'.format('csv'))
df_complete = pd.DataFrame()
exceptions = ["output/collectAggregatingReqOutput.csv", "output/wpserviceInput.csv"]

df_complete = pd.DataFrame()

print("merging the following files:")
for file in csv_files:
    if(file in exceptions):
        continue
    print(file)
    with open(file) as csv_file:
        data = csv_file.read().split(sep=";")
        df_complete.insert(0, Path(file).stem, data)

df_complete = df_complete.reindex(sorted(df_complete.columns), axis=1)
df_complete.drop(df_complete.tail(1).index, inplace=True)
df_complete.to_csv(path_or_buf="output.csv")