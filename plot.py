import plotly.graph_objects as go


fig = go.Figure()

fig.add_bar(y=[16.65], x=[1])
fig.add_bar(y=[15.6], x=[2])
fig.add_bar(y=[11.4895], x=[3])


fig.update_layout(
    title='Mutual Information',
    showlegend=False,
    xaxis=dict(
        tickvals=[1, 2, 3],
        ticktext=['scikit-learn', 'emi-6cores', 'emi-12cores']
    ),
    yaxis=dict(
        title='time',
        range=[0, 17]  # Use 'range' instead of 'ylim' for y-axis limits
    )
)
                  
fig.show()
fig.write_image("plot.png")