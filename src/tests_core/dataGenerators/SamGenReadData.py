import numpy as np

# Create a 10x3 array
data = np.array([
    [1.0, 2.0, 3.0],
    [4.0, 5.0, 6.0],
    [7.0, 8.0, 9.0],
    [10.0, 11.0, 12.0],
    [13.0, 14.0, 15.0],
    [16.0, 17.0, 18.0],
    [19.0, 20.0, 21.0],
    [22.0, 23.0, 24.0],
    [25.0, 26.0, 27.0],
    [28.0, 29.0, 30.0]
])

# Save to 'sample_data.npy' in the 'samples' directory
np.save('src/tests_core/samples/sample_data.npy', data)
print("Done!")