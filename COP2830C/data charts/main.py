import plotly.graph_objects as go


# Function to read the CSV file and return lists of altitude and mach numbers
def read_csv_data(filepath):
    altitudes = []
    mach_numbers = []

    try:
        with open(filepath, 'r') as file:
            next(file)

            for line in file:
                # Remove whitespace and split the lines then checks for two parts on each line.
                parts = line.strip().split(',')

                if len(parts) == 2:
                    try:
                        altitude = float(parts[0])
                        mach_number = float(parts[1])

                        altitudes.append(altitude)
                        mach_numbers.append(mach_number)

                    except (ValueError, IndexError):
                        # Skip this line if conversion fails.
                        continue

    except FileNotFoundError:
        print(f"Error: The file '{filepath}' was not found.")
        return None, None

    return altitudes, mach_numbers


# calls the read file function and gets the altitudes and mach_numbers
altitudes, mach_numbers = read_csv_data("alt_vs_speed.csv")

if altitudes is None or mach_numbers is None:
    exit()

# Create a figure
fig = go.Figure()

# Add the trace for Altitude vs. Mach Number
fig.add_trace(
    go.Scatter(
        x=mach_numbers,
        y=altitudes,
        mode='markers',
        name='Speed',
        marker=dict(color='LightSkyBlue', size=8, opacity=0.8)
    )
)

# Update the layout for the plot
fig.update_layout(
    title='Altitude vs. Speed',
    xaxis_title='Speed',
    yaxis_title='Altitude (feet)',
    template='plotly_dark'
)

# Save the plot to a single interactive HTML file
fig.write_html("altitude_vs_mach_number_plotly.html")

# Update the user with text that the chart was created.
print("Generated a single combined plot: 'altitude_vs_mach_number_plotly.html'")
