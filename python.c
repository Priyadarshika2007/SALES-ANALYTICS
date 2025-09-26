import pandas as pd
import matplotlib.pyplot as plt
df=pd.read_csv("/content/Sales (2).csv")

# Data cleaning
# Remove repeated rows if any
df.drop_duplicates(inplace=True)

# Drops completely empty rows
df.dropna(how='all', inplace=True)

# To trim whitespaces in column names
df.columns=df.columns.str.strip()

# To trim white spaces from string columns
for col in df.columns:
  if df[col].dtype=='object':
    df[col]=df[col].str.strip()

# Convert numeric columns
numeric_columns=['Rating','Selling Price','Original Price','Discount','discount percentage','Storage(GB)','Memory(GB)']
for col in numeric_columns:
  df[col]=pd.to_numeric(df[col],errors='coerce')

df['discount percentage'] = df['discount percentage'].fillna(0)
df['Discount'] = df['Discount'].fillna(0)
df['Sold'] = df['Sold'].fillna(0)
df['Rating'] = df['Rating'].fillna(df['Rating'].mean())
df['Storage(GB)'] = df['Storage(GB)'].fillna(df['Storage(GB)'].mean())
df['Memory(GB)'] = df['Memory(GB)'].fillna(df['Memory(GB)'].mean())
df['Selling Price'] = df['Selling Price'].fillna(df['Selling Price'].mean())
df['Original Price'] = df['Original Price'].fillna(df['Original Price'].mean())
df.fillna({'Brands' : 'Unknown','Models' : 'Unknown','Colors' : 'Unknown','Memory' : 'Unknown','Mobile' : 'Unknown'},inplace=True)

# Analysis
df['Total Sale']=df['Selling Price']*df['Sold']
total_sales=df['Total Sale'].sum()
print("Total Sales amount: ",total_sales)

total_sold=df['Sold'].sum()
print("Total sold phones: ",total_sold)

average_sales=total_sales/total_sold
print("Average sales of phone: ",average_sales)
# or average_sales=df['Total Sale'].mean()

sales_by_product=df.groupby('Brands')['Total Sale'].sum().sort_values(ascending=False)
print("Sales by product top 10 : \n", sales_by_product.head(10))


# Visualization by bar chart based top 10 brands
top_brands=sales_by_product.head(10)
plt.figure(figsize=(10,6))
top_brands.plot(kind='bar')
plt.xlabel('Brands')
plt.ylabel('Total Sale')
plt.title('Top 10 Brands by Total Sale')
plt.show()

top_brands_by_storage=df.groupby('Brands')['Storage(GB)'].mean().sort_values(ascending=False)
print("Top 10 brands by storage : \n", top_brands_by_storage.head(10))

# Visualisation in line chart of top 10 brands based on storage
top_brands_by_storage=top_brands_by_storage.head(10)
plt.figure(figsize=(10,6))
top_brands_by_storage.plot(kind='line')

