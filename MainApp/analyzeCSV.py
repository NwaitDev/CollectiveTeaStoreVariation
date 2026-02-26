import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

df_complete = pd.read_csv("output.csv")

for i in range(4):
    colname = "responseTime" + str(i)
    basecol = "feedback" + str(i)
    df_complete[colname] = np.where(
        (df_complete[basecol] > df_complete[basecol].shift(1)) &
        (df_complete[basecol] > df_complete[basecol].shift(-1)),
        df_complete[basecol],
        0
    )

    df_complete[colname + "smooth"] = (
        df_complete[colname]
        .where(df_complete[colname] != 0)
        .rolling(window=50, min_periods=1)
        .mean()
        .fillna(0)
    )

    plt.plot(df_complete[colname + "smooth"])
    plt.xlabel("ticks")
    plt.ylabel("average response time")
    plt.savefig(colname+".png")
    # plt.show()
    plt.clf()

    plt.plot(df_complete["ctrl"+str(i)+"command"])
    plt.xlabel("ticks")
    plt.ylabel("cache size")
    plt.savefig("cache size"+str(i)+".png")
    plt.clf()

df_complete.to_csv(path_or_buf="TreatedOutput.csv")